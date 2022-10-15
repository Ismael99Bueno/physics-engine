#include "body2D.hpp"

namespace physics2D
{
    body::body(const vec2 &pos) : m_pos(pos) {}
    body::body(const vec2 &pos, const vec2 &vel) : m_pos(pos), m_vel(vel) {}
    body::body(const vec2 &pos, const vec2 &vel, double mass) : m_pos(pos), m_vel(vel), m_mass(mass) {}
    body::body(const vec2 &pos, const vec2 &vel, double mass, double charge) : m_pos(pos),
                                                                               m_vel(vel),
                                                                               m_mass(mass),
                                                                               m_charge(charge) {}

    vec2 &body::position() { return m_pos; }
    const vec2 &body::position() const { return m_pos; }
    vec2 &body::vel() { return m_vel; }
    const vec2 &body::vel() const { return m_vel; }
    double body::mass() const { return m_mass; }
    double body::charge() const { return m_charge; }
}