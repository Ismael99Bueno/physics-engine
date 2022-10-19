#include "collider2D.hpp"

namespace physics
{
    collider2D::collider2D(const body2D &body) : entity2D(body) {}
    collider2D::collider2D(const vec::vec2 &dim) : entity2D(), m_bbox(dim, m_buffer) {}
    collider2D::collider2D(const body2D &body, const vec::vec2 &dim) : entity2D(body), m_bbox(dim, m_buffer) {}

    void collider2D::retrieve()
    {
        entity2D::retrieve();
        m_bbox.retrieve();
    }

    const bbox2D &collider2D::bbox() const { return m_bbox; }
}