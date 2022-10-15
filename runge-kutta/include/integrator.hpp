#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "tableau.hpp"
#include <cstdint>

namespace rk
{
    class integrator
    {
    private:
        using vector = std::vector<double>;
        using matrix = std::vector<std::vector<double>>;
        using uint8 = std::uint8_t;
        using uint32 = std::uint32_t;

    public:
        integrator() = delete;
        integrator(const tableau &tb,
                   vector &state,
                   double tolerance = 1e-6,
                   double min_dt = 1e-6,
                   double max_dt = 1.0);

        template <typename T>
        void raw_forward(double &t,
                         double dt,
                         const T &params,
                         vector (*ode)(double, const vector &, const T &));

        template <typename T>
        void reiterative_forward(double &t,
                                 double &dt,
                                 const T &params,
                                 vector (*ode)(double, const vector &, const T &),
                                 uint8 reiterations = 2);

        template <typename T>
        void embedded_forward(double &t,
                              double &dt,
                              const T &params,
                              vector (*ode)(double, const vector &, const T &));

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
        vector &m_state;
        mutable matrix m_kvec;
        double m_tolerance, m_min_dt, m_max_dt, m_error;
        bool m_valid;

        void resize_kvec() const;

        template <typename T>
        void update_kvec(double t,
                         double dt,
                         const vector &state,
                         const T &params,
                         vector (*ode)(double, const vector &, const T &)) const;

        vector generate_solution(double dt,
                                 const vector &state,
                                 const vector &coefs);

        bool dt_too_small(double dt) const;
        bool dt_too_big(double dt) const;
        bool dt_off_bounds(double dt) const;
        static double embedded_error(const vector &sol1, const vector &sol2);
        double reiterative_error(const vector &sol1, const vector &sol2) const;
    };
}

#include "integrator.tpp"

#endif