#ifndef ODE2D_HPP
#define ODE2D_HPP

#include "engine2D.hpp"
#include "force2D.hpp"

namespace physics
{
    vec2 apply_force(const entity2D &entity, const force2D &force);
    std::vector<float> ode(const float t, const std::vector<float> &state, const engine2D &eng);
}

#endif