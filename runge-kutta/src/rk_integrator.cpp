#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

#define SAFETY_FACTOR 0.85
#define TOL_PART 256.0

namespace rk
{
    integrator::integrator(const tableau &tb,
                           const double tolerance,
                           const double min_dt,
                           const double max_dt) : m_tableau(tb),
                                                  m_tolerance(tolerance),
                                                  m_min_dt(min_dt),
                                                  m_max_dt(max_dt),
                                                  m_error(0.0),
                                                  m_valid(true) {}

    integrator::integrator(tableau &&tb,
                           const double tolerance,
                           const double min_dt,
                           const double max_dt) : m_tableau(std::move(tb)),
                                                  m_tolerance(tolerance),
                                                  m_min_dt(min_dt),
                                                  m_max_dt(max_dt),
                                                  m_error(0.0),
                                                  m_valid(true) {}

    integrator::vector2d integrator::reserve(const uint32 n, const uint32 m)
    {
        vector2d v;
        v.reserve(n);
        for (vector1d &v : v)
            v.reserve(m);
        return v;
    }

    integrator::vector2d integrator::k_vectors(const double t,
                                               const double dt,
                                               const vector1d &vars,
                                               vector1d (*ode)(double, const vector1d &)) const
    {
        vector2d kvec = reserve(m_tableau.stage(), vars.size());
        vector1d vars_aux(vars.size());

        kvec.emplace_back(ode(t, vars));
        for (uint8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < vars.size(); j++)
            {
                double k_sum = 0.0;
                for (uint8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * kvec[k][j];
                vars_aux[j] = vars[j] + k_sum * dt;
            }
            kvec.emplace_back(ode(t, vars_aux));
        }
        return kvec;
    }

    integrator::vector1d integrator::generate_solution(const double dt,
                                                       const vector2d &kvec,
                                                       const vector1d &vars,
                                                       const vector1d &coefs) const
    {
        vector1d sol;
        sol.reserve(vars.size());
        for (std::size_t j = 0; j < vars.size(); j++)
        {
            double sum = 0.0;
            for (uint8 i = 0; i < m_tableau.stage(); i++)
                sum += coefs[i] * kvec[i][j];
            m_valid &= !isnan(sum);
            DBG_LOG_IF(!m_valid, "NaN encountered when computing runge-kutta solution")
            sol.emplace_back(vars[j] + sum * dt);
        }
        return sol;
    }

    integrator::vector1d integrator::integrate(double t,
                                               double dt,
                                               const vector1d &vars,
                                               const vector1d &coefs,
                                               vector1d (*ode)(double, const vector1d &)) const
    {
        const vector2d kvec = k_vectors(t, dt, vars, ode);
        return generate_solution(dt, kvec, vars, coefs);
    }

    integrator::vector1d integrator::raw_forward(double &t,
                                                 const double dt,
                                                 const vector1d &vars,
                                                 vector1d (*ode)(double, const vector1d &)) const
    {
        m_valid = true;
        const vector2d kvec = k_vectors(t, dt, vars, ode);
        const vector1d sol = generate_solution(dt, kvec, vars, m_tableau.coefs());
        t += dt;
        return sol;
    }

    integrator::vector1d integrator::reiterative_forward(double &t,
                                                         double &dt,
                                                         const vector1d &vars,
                                                         vector1d (*ode)(double, const vector1d &)) const
    {
        DBG_LOG_IF(m_tableau.embedded(), "Table has an embedded solution. Use an embedded adaptive method for better efficiency")
        vector1d sol;
        for (;;)
        {
            const vector1d aux_sol = integrate(t, dt, vars, m_tableau.coefs(), ode);
            integrate(t, dt / 2.0, vars, m_tableau.coefs(), ode).swap(sol);
            integrate(t, dt / 2.0, sol, m_tableau.coefs(), ode).swap(sol);
            m_error = reiterative_error(sol, aux_sol);
            if (dt_off_bounds(dt) || m_error <= m_tolerance)
                break;
            dt /= 2.0;
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;
        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / m_tableau.order()), m_min_dt, m_max_dt);
        return sol;
    }

    integrator::vector1d integrator::embedded_forward(double &t,
                                                      double &dt,
                                                      const vector1d &vars,
                                                      vector1d (*ode)(double, const vector1d &)) const
    {
        DBG_EXIT_IF(!m_tableau.embedded(), "Cannot perform embedded adaptive stepsize without an embedded solution.\n")
        vector1d sol;
        for (;;)
        {
            const vector2d kvec = k_vectors(t, dt, vars, ode);
            generate_solution(dt, kvec, vars, m_tableau.coefs1()).swap(sol);
            const vector1d aux_sol = generate_solution(dt, kvec, vars, m_tableau.coefs2());
            m_error = embedded_error(sol, aux_sol);
            if (dt_off_bounds(dt) || m_error <= m_tolerance)
                break;
            dt *= SAFETY_FACTOR * pow(m_tolerance / m_error, 1.0 / m_tableau.order());
        }
        m_error = std::max(m_error, m_tolerance / TOL_PART);
        t += dt;
        dt = std::clamp(SAFETY_FACTOR * dt * std::pow(m_tolerance / m_error, 1.0 / (m_tableau.order() - 1)), m_min_dt, m_max_dt);
        return sol;
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

    bool integrator::dt_off_bounds(const double dt) const { return dt <= m_min_dt || dt >= m_max_dt; }

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