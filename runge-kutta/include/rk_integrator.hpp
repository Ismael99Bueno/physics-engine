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
        integrator(const tableau &tb,
                   vector1d &state,
                   double tolerance = 1e-6,
                   double min_dt = 1e-6,
                   double max_dt = 1.0);
        integrator(tableau &&tb,
                   vector1d &state,
                   double tolerance = 1e-6,
                   double min_dt = 1e-6,
                   double max_dt = 1.0);

        void raw_forward(double &t,
                         double dt,
                         vector1d (*ode)(double, const vector1d &));

        void reiterative_forward(double &t,
                                 double &dt,
                                 vector1d (*ode)(double, const vector1d &));

        void embedded_forward(double &t,
                              double &dt,
                              vector1d (*ode)(double, const vector1d &));

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
        vector1d &m_state;
        mutable vector2d m_kvec;
        double m_tolerance, m_min_dt, m_max_dt;
        mutable double m_error;
        mutable bool m_valid;

        void resize_kvec() const;

        void update_kvec(double t,
                         double dt,
                         vector1d (*ode)(double, const vector1d &)) const;

        vector1d generate_solution(double dt,
                                   const vector1d &coefs) const;

        vector1d integrate(double t,
                           double dt,
                           const vector1d &coefs,
                           vector1d (*ode)(double, const vector1d &)) const;

        bool dt_too_small(double dt) const;
        bool dt_too_big(double dt) const;
        bool dt_off_bounds(double dt) const;
        static double embedded_error(const vector1d &sol1, const vector1d &sol2);
        double reiterative_error(const vector1d &sol1, const vector1d &sol2) const;
    };
}

#endif