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
                                 const vector1d &state,
                                 const T &params,
                                 vector1d (*ode)(double, const vector1d &, const T &)) const
    {
        vector1d aux_state(state.size());

        m_kvec[0] = ode(t, state, params);
        for (uint8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < state.size(); j++)
            {
                double k_sum = 0.0;
                for (uint8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * m_kvec[k][j];
                aux_state[j] = state[j] + k_sum * dt;
            }
            m_kvec[i] = ode(t + m_tableau.alpha()[i - 1] * dt, aux_state, params);
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
        update_kvec(t, dt, m_state, params, ode);
        m_state = generate_solution(dt, m_state, m_tableau.coefs());
        t += dt;
    }

    template <typename T>
    void integrator::reiterative_forward(double &t,
                                         double &dt,
                                         const T &params,
                                         vector1d (*ode)(double, const vector1d &, const T &),
                                         const uint8 reiterations)
    {
        DBG_EXIT_IF(reiterations < 2, "The amount of reiterations has to be greater than 1, otherwise the algorithm will break.\n")
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        DBG_LOG_IF(m_tableau.embedded(), "Table has an embedded solution. Use an embedded adaptive method for better efficiency.\n")
        m_valid = true;
        for (;;)
        {
            vector1d sol1 = m_state;
            for (uint8 i = 0; i < reiterations; i++)
            {
                update_kvec(t, dt / reiterations, sol1, params, ode);
                sol1 = generate_solution(dt / reiterations, sol1, m_tableau.coefs());
            }

            update_kvec(t, dt, m_state, params, ode);
            const vector1d sol2 = generate_solution(dt, m_state, m_tableau.coefs());
            m_error = reiterative_error(sol1, sol2);
            if (m_error <= m_tolerance || dt_too_small(dt))
            {
                m_state = sol1;
                break;
            }
            dt *= SAFETY_FACTOR * std::pow(m_tolerance / m_error, 1.0 / (m_tableau.order() + 1U));
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
            update_kvec(t, dt, m_state, params, ode);
            const vector1d sol1 = generate_solution(dt, m_state, m_tableau.coefs1());
            const vector1d sol2 = generate_solution(dt, m_state, m_tableau.coefs2());
            m_error = embedded_error(sol1, sol2);

            if (m_error <= m_tolerance || dt_too_small(dt))
            {
                m_state = sol1;
                break;
            }
            dt *= SAFETY_FACTOR * pow(m_tolerance / m_error, 1.0 / m_tableau.order());
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;
        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / (m_tableau.order() - 1)), m_min_dt, m_max_dt);
    }
}