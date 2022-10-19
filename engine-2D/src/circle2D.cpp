#include "circle2D.hpp"

namespace physics
{
    circle2D::circle2D(const body2D &body, const float radius) : collider2D(body), m_radius(radius) {}
    circle2D::circle2D(const vec::vec2 &dim, const float radius) : collider2D(dim), m_radius(radius) {}
    circle2D::circle2D(const body2D &body, const vec::vec2 &dim, const float radius) : collider2D(body, dim), m_radius(radius) {}

    bool circle2D::overlaps(const circle2D &circle) const
    {
        const float sq_dist = circle.body().pos().sq_dist(m_body.pos());
        const float R = m_radius + circle.radius();
        return sq_dist <= R * R;
    }

    float circle2D::radius() const { return m_radius; }
    void circle2D::radius(float radius) { m_radius = radius; }
}