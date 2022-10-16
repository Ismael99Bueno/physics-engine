#include "interaction2D.hpp"
#include "debug.h"

namespace physics
{
    interaction2D::interaction2D(const std::size_t allocations) { m_entities.reserve(allocations); }

    void interaction2D::add(const entity2D &entity) { m_entities.insert(&entity); }
    void interaction2D::remove(const entity2D &entity) { m_entities.erase(&entity); }
    bool interaction2D::contains(const entity2D &entity) const { return m_entities.find(&entity) != m_entities.end(); }

    std::unordered_set<const entity2D *> &interaction2D::entities() { return m_entities; }
    const std::unordered_set<const entity2D *> &interaction2D::entities() const { return m_entities; }
}