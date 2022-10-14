#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

#define SAFETY_FACTOR 0.85
#define TOL_PART 256.0

namespace rk
{
    integrator::integrator(const tableau &tb,
                           vector1d &state,
                           const double tolerance,
                           const double min_dt,
                           const double max_dt) : m_tableau(tb),
                                                  m_state(state),
                                                  m_tolerance(tolerance),
                                                  m_min_dt(min_dt),
                                                  m_max_dt(max_dt),
                                                  m_error(0.0),
                                                  m_valid(true) { resize_kvec(); }

    integrator::integrator(tableau &&tb,
                           vector1d &state,
                           const double tolerance,
                           const double min_dt,
                           const double max_dt) : m_tableau(std::move(tb)),
                                                  m_state(state),
                                                  m_tolerance(tolerance),
                                                  m_min_dt(min_dt),
                                                  m_max_dt(max_dt),
                                                  m_error(0.0),
                                                  m_valid(true) { resize_kvec(); }

    void integrator::resize_kvec() const
    {
        m_kvec.resize(m_tableau.stage());
        for (vector1d &v : m_kvec)
            v.resize(m_state.size());
    }

    void integrator::update_kvec(const double t,
                                 const double dt,
                                 vector1d (*ode)(double, const vector1d &)) const
    {
        vector1d aux_state(m_state.size());

        m_kvec[0] = ode(t, m_state);
        for (uint8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < m_state.size(); j++)
            {
                double k_sum = 0.0;
                for (uint8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * m_kvec[k][j];
                aux_state[j] = m_state[j] + k_sum * dt;
            }
            m_kvec[i] = ode(t, aux_state);
        }
    }

    integrator::vector1d integrator::generate_solution(const double dt,
                                                       const vector1d &coefs) const
    {
        vector1d sol;
        sol.reserve(m_state.size());
        for (std::size_t j = 0; j < m_state.size(); j++)
        {
            double sum = 0.0;
            for (uint8 i = 0; i < m_tableau.stage(); i++)
                sum += coefs[i] * m_kvec[i][j];
            m_valid &= !isnan(sum);
            DBG_LOG_IF(!m_valid, "NaN encountered when computing runge-kutta solution.\n")
            sol.emplace_back(m_state[j] + sum * dt);
        }
        return sol;
    }

    integrator::vector1d integrator::integrate(double t,
                                               double dt,
                                               const vector1d &coefs,
                                               vector1d (*ode)(double, const vector1d &)) const
    {
        update_kvec(t, dt, ode);
        return generate_solution(dt, coefs);
    }

    void integrator::raw_forward(double &t,
                                 const double dt,
                                 vector1d (*ode)(double, const vector1d &))
    {
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        m_valid = true;
        update_kvec(t, dt, ode);
        generate_solution(dt, m_tableau.coefs()).swap(m_state);
        t += dt;
    }

    void integrator::reiterative_forward(double &t,
                                         double &dt,
                                         vector1d (*ode)(double, const vector1d &))
    {
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        DBG_LOG_IF(m_tableau.embedded(), "Table has an embedded solution. Use an embedded adaptive method for better efficiency.\n")
        m_valid = true;
        for (;;)
        {
            const vector1d aux_sol = integrate(t, dt, m_tableau.coefs(), ode);
            integrate(t, dt / 2.0, m_tableau.coefs(), ode).swap(m_state);
            integrate(t, dt / 2.0, m_tableau.coefs(), ode).swap(m_state);
            m_error = reiterative_error(m_state, aux_sol);
            if (m_error <= m_tolerance || dt_too_small(dt))
                break;
            dt /= 2.0;
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;

        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / m_tableau.order()), m_min_dt, m_max_dt);
    }

    void integrator::embedded_forward(double &t,
                                      double &dt,
                                      vector1d (*ode)(double, const vector1d &))
    {
        DBG_EXIT_IF(!m_tableau.embedded(), "Cannot perform embedded adaptive stepsize without an embedded solution.\n")
        DBG_EXIT_IF(dt_off_bounds(dt), "Timestep is not between established limits. Change the timestep or adjust the limits to include the current value.\n")
        m_valid = true;
        for (;;)
        {
            update_kvec(t, dt, ode);
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

    static std::uint32_t ipow(std::uint32_t base, std::uint32_t exponent)
    {
        int result = 1;
        for (;;)
        {
            if (exponent & 1)
                result *= base;
            exponent >>= 1;
            if (!exponent)
                break;
            base *= base;
        }

        return result;
    }

    bool integrator::dt_too_small(const double dt) const { return dt < m_min_dt; }
    bool integrator::dt_too_big(const double dt) const { return dt > m_max_dt; }
    bool integrator::dt_off_bounds(const double dt) const { return dt_too_small(dt) || dt_too_big(dt); }

    double integrator::embedded_error(const vector1d &sol1, const vector1d &sol2)
    {
        double result = 0.0;
        for (std::size_t i = 0; i < sol1.size(); i++)
            result += (sol1[i] - sol2[i]) * (sol1[i] - sol2[i]);
        return result;
    }

    double integrator::reiterative_error(const vector1d &sol1, const vector1d &sol2) const
    {
        const uint32 coeff = ipow(2, m_tableau.order()) - 1;
        return embedded_error(sol1, sol2) / coeff;
    }

    double integrator::tolerance() const { return m_tolerance; }
    double integrator::min_dt() const { return m_min_dt; }
    double integrator::max_dt() const { return m_max_dt; }
    double integrator::error() const { return m_error; }
    bool integrator::valid() const { return m_valid; }

    void integrator::tolerance(const double val) { m_tolerance = val; }
    void integrator::min_dt(const double val) { m_min_dt = val; }
    void integrator::max_dt(const double val) { m_max_dt = val; }
}