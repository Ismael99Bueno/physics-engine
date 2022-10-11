#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

namespace rk
{
    integrator::integrator(const tableau &tb) : m_tableau(tb) {}

    integrator::integrator(tableau &&tb) : m_tableau(std::move(tb)) {}

    integrator::vector2d integrator::reserve(const int32 n, const int32 m)
    {
        vector2d v;
        v.reserve(n);
        for (vector1d &v : v)
            v.reserve(m);
        return v;
    }

    integrator::vector2d integrator::k_vectors(double t,
                                               double dt,
                                               const vector1d &vars,
                                               vector1d (*ode)(double, const vector1d &)) const
    {
        vector2d k_vectors = reserve(m_tableau.stage(), vars.size());
        vector1d vars_aux;
        vars_aux.reserve(vars.size());

        k_vectors.emplace_back(ode(t, vars));
        for (int8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < vars.size(); j++)
            {
                double k_sum = 0.0;
                for (int8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * k_vectors[k][j];
                vars_aux[j] = vars[j] + k_sum * dt;
            }
            k_vectors[i] = ode(t, vars_aux);
        }
        return k_vectors;
    }

    integrator::vector1d integrator::generate_solution(double dt,
                                                       const vector2d &k_vectors,
                                                       const vector1d &vars,
                                                       const vector1d &coefs) const
    {
        vector1d sol;
        sol.reserve(vars.size());
        for (std::size_t j = 0; j < vars.size(); j++)
        {
            double sum = 0.0;
            for (int8 i = 0; i < m_tableau.stage(); i++)
                sum += coefs[i] * k_vectors[i][j];
            DBG_LOG_IF(isnan(sum), "NaN encountered when computing runge-kutta solution")
            sol[j] = vars[j] + sum * dt;
        }
        return sol;
    }
}