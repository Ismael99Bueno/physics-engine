#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

namespace rk
{
    integrator::integrator(const tableau &tb,
                           const double tolerance = 1e-6,
                           const double min_dt = 1.e-6,
                           const double max_dt = 1.0) : m_tableau(tb),
                                                        m_tolerance(tolerance),
                                                        m_min_dt(min_dt),
                                                        m_max_dt(max_dt) {}

    integrator::integrator(tableau &&tb,
                           const double tolerance = 1e-6,
                           const double min_dt = 1.e-6,
                           const double max_dt = 1.0) : m_tableau(std::move(tb)),
                                                        m_tolerance(tolerance),
                                                        m_min_dt(min_dt),
                                                        m_max_dt(max_dt) {}

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
            DBG_LOG_IF(isnan(sum), "NaN encountered when computing runge-kutta solution")
            sol.emplace_back(vars[j] + sum * dt);
        }
        return sol;
    }

    integrator::vector1d integrator::raw_forward(double &t,
                                                 const double dt,
                                                 const vector1d &vars,
                                                 vector1d (*ode)(double, const vector1d &)) const
    {
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
        vector1d sol, aux_sol;
        double error;
        do
        {
        } while (error > m_tolerance);
    }

    std::uint32_t ipow(std::uint32_t base, std::uint32_t exponent)
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
}