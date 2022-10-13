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
        using uint8 = std::uint8_t;
        using uint32 = std::uint32_t;

    public:
        integrator() = delete;
        integrator(const tableau &tb, double tolerance = 1e-6, double min_dt = 1e-6, double max_dt = 1.0);
        integrator(tableau &&tb, double tolerance = 1e-6, double min_dt = 1e-6, double max_dt = 1.0);

        vector1d raw_forward(double &t,
                             double dt,
                             const vector1d &vars,
                             vector1d (*ode)(double, const vector1d &)) const;

        vector1d reiterative_forward(double &t,
                                     double &dt,
                                     const vector1d &vars,
                                     vector1d (*ode)(double, const vector1d &)) const;

        vector1d embedded_forward(double &t,
                                  double &dt,
                                  const vector1d &vars,
                                  vector1d (*ode)(double, const vector1d &)) const;

        double tolerance() const;
        double min_dt() const;
        double max_dt() const;
        double error() const;
        bool valid() const;

        void tolerance(double val);
        void min_dt(double val);
        void max_dt(double val);

    private:
        const tableau m_tableau;
        double m_tolerance, m_min_dt, m_max_dt;
        mutable double m_error;
        mutable bool m_valid;

        static vector2d reserve(uint32 n, uint32 m);

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

        vector1d integrate(double t,
                           double dt,
                           const vector1d &vars,
                           const vector1d &coefs,
                           vector1d (*ode)(double, const vector1d &)) const;

        bool dt_off_bounds(double dt) const;
        static double embedded_error(const vector1d &sol1, const vector1d &sol2);
        double reiterative_error(const vector1d &sol1, const vector1d &sol2) const;
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
        for (uint8 i = 1; i < m_tableau.stage(); i++)
        {
            for (std::size_t j = 0; j < vars.size(); j++)
            {
                double k_sum = 0.0;
                for (uint8 k = 0; k < i; k++)
                    k_sum += m_tableau.beta()[i - 1][k] * k_vectors[k][j];
                vars_aux[j] = vars[j] + k_sum * dt;
            }
            k_vectors[i] = ode(t, vars_aux, params);
        }
        return k_vectors;
    }
}

#endif