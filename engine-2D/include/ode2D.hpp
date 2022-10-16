#ifndef ODE2D_HPP
#define ODE2D_HPP

#include "engine2D.hpp"
#include "force2D.hpp"

namespace physics
{
    vec2 apply_force(const entity2D &entity, const force2D &force);
    std::vector<double> ode(const double t, const std::vector<double> &state, const engine2D &eng);
}

#endif