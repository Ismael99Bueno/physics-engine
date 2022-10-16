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
        body2D(const vec2 &pos, const vec2 &vel, double mass);
        body2D(const vec2 &pos, const vec2 &vel, double mass, double charge);

        vec2 &pos();
        vec2 &vel();
        const vec2 &pos() const;
        const vec2 &vel() const;
        double mass() const;
        double charge() const;

        void pos(const vec2 &pos);
        void vel(const vec2 &vel);
        void mass(double mass);
        void charge(double charge);

    private:
        vec2 m_pos, m_vel;
        double m_mass = 1.0, m_charge = 1.0;
    };
}

#endif