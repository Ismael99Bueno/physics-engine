#include "entity2D.hpp"

namespace physics
{
    entity2D::entity2D(const body2D &body) : m_body(body) {}

    void entity2D::retrieve() {}

    body2D &entity2D::body() { return m_body; }
    const body2D &entity2D::body() const { return m_body; }
}