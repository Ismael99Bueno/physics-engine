#include "body2D.hpp"

namespace physics
{
    body2D::body2D(const vec2 &pos) : m_pos(pos) {}
    body2D::body2D(const vec2 &pos, const vec2 &vel) : m_pos(pos), m_vel(vel) {}
    body2D::body2D(const vec2 &pos, const vec2 &vel, const float mass) : m_pos(pos), m_vel(vel), m_mass(mass) {}
    body2D::body2D(const vec2 &pos, const vec2 &vel, const float mass, const float charge) : m_pos(pos),
                                                                                             m_vel(vel),
                                                                                             m_mass(mass),
                                                                                             m_charge(charge) {}

    vec2 &body2D::pos() { return m_pos; }
    vec2 &body2D::vel() { return m_vel; }
    const vec2 &body2D::pos() const { return m_pos; }
    const vec2 &body2D::vel() const { return m_vel; }
    float body2D::mass() const { return m_mass; }
    float body2D::charge() const { return m_charge; }

    void body2D::pos(const vec2 &pos) { m_pos = pos; }
    void body2D::vel(const vec2 &vel) { m_vel = vel; }
    void body2D::mass(float mass) { m_mass = mass; }
    void body2D::charge(float charge) { m_charge = charge; }
}