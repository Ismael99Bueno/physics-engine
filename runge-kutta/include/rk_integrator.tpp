#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

#define SAFETY_FACTOR 0.85
#define TOL_PART 256.0

namespace rk
{
    template <typename T>
    void integrator::update_kvec(const double t,
                                 const double dt,
                                 const T &params,
                                 vector1d (*ode)(double, const vector1d &, const T &)) const
    {
        vector1d aux_state(m_state.size());

        m_kvec[0] = ode(t, m_state, params);
        for (uint8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < m_state.size(); j++)
            {
                double k_sum = 0.0;
                for (uint8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * m_kvec[k][j];
                aux_state[j] = m_state[j] + k_sum * dt;
            }
            m_kvec[i] = ode(t, aux_state, params);
        }
    }

    template <typename T>
    void integrator::raw_forward(double &t,
                                 const double dt,
                                 const T &params,
                                 vector1d (*ode)(double, const vector1d &, const T &))
    {
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        m_valid = true;
        update_kvec(t, dt, params, ode);
        generate_solution(dt, m_tableau.coefs()).swap(m_state);
        t += dt;
    }

    template <typename T>
    void integrator::reiterative_forward(double &t,
                                         double &dt,
                                         const T &params,
                                         vector1d (*ode)(double, const vector1d &, const T &),
                                         const uint8 reiterations)
    {
        DBG_EXIT_IF(reiterations < 2, "The amount of reiteration has to be greater than 1, otherwise the algorithm will break.\n")
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        DBG_LOG_IF(m_tableau.embedded(), "Table has an embedded solution. Use an embedded adaptive method for better efficiency.\n")
        m_valid = true;
        for (;;)
        {
            update_kvec(t, dt, params, ode);
            const vector1d aux_sol = generate_solution(dt, m_tableau.coefs());
            for (uint8 i = 0; i < reiterations; i++)
            {
                update_kvec(t, dt / reiterations, params, ode);
                generate_solution(dt / reiterations, m_tableau.coefs()).swap(m_state);
            }
            m_error = reiterative_error(m_state, aux_sol);
            if (m_error <= m_tolerance || dt_too_small(dt))
                break;
            dt /= 2.0;
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;
        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / m_tableau.order()), m_min_dt, m_max_dt);
    }

    template <typename T>
    void integrator::embedded_forward(double &t,
                                      double &dt,
                                      const T &params,
                                      vector1d (*ode)(double, const vector1d &, const T &))
    {
        DBG_EXIT_IF(!m_tableau.embedded(), "Cannot perform embedded adaptive stepsize without an embedded solution.\n")
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        m_valid = true;
        for (;;)
        {
            update_kvec(t, dt, params, ode);
            const vector1d aux_sol = generate_solution(dt, m_tableau.coefs2());
            generate_solution(dt, m_tableau.coefs1()).swap(m_state);
            m_error = embedded_error(m_state, aux_sol);

            if (m_error <= m_tolerance || dt_too_small(dt))
                break;
            dt *= SAFETY_FACTOR * pow(m_tolerance / m_error, 1.0 / m_tableau.order());
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;
        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / (m_tableau.order() - 1)), m_min_dt, m_max_dt);
    }
}