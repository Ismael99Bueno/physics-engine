#ifndef BODY2D_HPP
#define BODY2D_HPP

#include "vec2.hpp"

namespace physics
{
    using namespace vec;
    class body2D
    {
    public:
        body2D() = default;
        body2D(const vec2 &pos);
        body2D(const vec2 &pos, const vec2 &vel);
        body2D(const vec2 &pos, const vec2 &vel, float mass);
        body2D(const vec2 &pos, const vec2 &vel, float mass, float charge);

        vec2 &pos();
        vec2 &vel();
        const vec2 &pos() const;
        const vec2 &vel() const;
        float mass() const;
        float charge() const;

        void pos(const vec2 &pos);
        void vel(const vec2 &vel);
        void mass(float mass);
        void charge(float charge);

    private:
        vec2 m_pos, m_vel;
        float m_mass = 1.f, m_charge = 1.f;
    };
}

#endif