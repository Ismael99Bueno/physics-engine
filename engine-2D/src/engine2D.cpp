#include "engine2D.hpp"

namespace physics
{
    engine2D::engine2D(const rk::tableau &tableau,
                       const double dt,
                       const std::uint32_t allocations) : m_integ(tableau, m_buffer), m_dt(dt)
    {
        m_entities.reserve(allocations);
        m_integ.reserve_state(4 * allocations);
    }

    void engine2D::add(const entity2D &entity)
    {
        m_buffer.emplace_back(entity.body().pos().x);
        m_buffer.emplace_back(entity.body().pos().y);
        m_buffer.emplace_back(entity.body().vel().x);
        m_buffer.emplace_back(entity.body().vel().y);
        m_entities.emplace_back(entity);
        entity.m_buffer = &m_buffer[m_buffer.size() - 4];
    }

    void engine2D::add(const std::vector<entity2D> &entities)
    {
        for (const entity2D &entity : entities)
            add(entity);
    }
}