#ifndef RK_INTEGRATOR_HPP
#define RK_INTEGRATOR_HPP

#include "rk_tableau.hpp"
#include <cstdint>

namespace rk
{
    class integrator
    {
    private:
        using vector1d = std::vector<double>;
        using vector2d = std::vector<std::vector<double>>;
        using int8 = std::uint8_t;
        using int32 = std::uint32_t;

    public:
        integrator() = delete;
        integrator(const tableau &tb);
        integrator(tableau &&tb);

    private:
        tableau m_tableau;

        static vector2d reserve(int32 n, int32 m);

        vector2d k_vectors(double t,
                           double dt,
                           const vector1d &vars,
                           vector1d (*ode)(double, const vector1d &)) const;

        template <typename T>
        vector2d k_vectors(double t,
                           double dt,
                           const vector1d &vars,
                           T &params,
                           vector1d (*ode)(double, const vector1d &, T &)) const;

        vector1d generate_solution(double dt,
                                   const vector2d &k_vectors,
                                   const vector1d &vars,
                                   const vector1d &coefs) const;
    };

    template <typename T>
    integrator::vector2d integrator::k_vectors(double t,
                                               double dt,
                                               const vector1d &vars,
                                               T &params,
                                               vector1d (*ode)(double, const vector1d &, T &)) const
    {
        vector2d k_vectors = reserve(m_tableau.stage(), vars.size());
        vector1d vars_aux;
        vars_aux.reserve(vars.size());

        k_vectors.emplace_back(ode(t, vars, params));
        for (int8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < vars.size(); j++)
            {
                double k_sum = 0.0;
                for (int8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * k_vectors[k][j];
                vars_aux[j] = vars[j] + k_sum * dt;
            }
            k_vectors[i] = ode(t, vars_aux, params);
        }
        return k_vectors;
    }
}

#endif