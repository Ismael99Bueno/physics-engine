#ifndef RUNGEKUTTA_HPP
#define RUNGEKUTTA_HPP

#include "butcher_tableau.hpp"
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
    };
}

#endif