#include "force2D.hpp"

namespace physics
{
    force2D::force2D(const std::size_t allocations) { m_entities.reserve(allocations); }

    void force2D::add(const entity2D &entity) { m_entities.insert(&entity); }
    void force2D::remove(const entity2D &entity) { m_entities.erase(&entity); }
    bool force2D::contains(const entity2D &entity) const { return m_entities.find(&entity) != m_entities.end(); }

    std::unordered_set<const entity2D *> &force2D::entities() { return m_entities; }
    const std::unordered_set<const entity2D *> &force2D::entities() const { return m_entities; }
}