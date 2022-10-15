#ifndef BODY2D_HPP
#define BODY2D_HPP

#include "vec2.hpp"
using namespace vec;

namespace physics
{
    class body2D
    {
    public:
        body2D() = default;
        body2D(const vec2 &pos);
        body2D(const vec2 &pos, const vec2 &vel);
        body2D(const vec2 &pos, const vec2 &vel, double mass);
        body2D(const vec2 &pos, const vec2 &vel, double mass, double charge);

        vec2 &position();
        const vec2 &position() const;
        vec2 &vel();
        const vec2 &vel() const;
        double mass() const;
        double charge() const;

    private:
        vec2 m_pos = {0.0, 0.0}, m_vel = {0.0, 0.0};
        double m_mass = 1.0, m_charge = 1.0;
    };
}

#endif