#include "ode2D.hpp"
#include "engine2D.hpp"
#include "debug.h"

namespace physics
{
    engine2D::engine2D(const rk::tableau &tableau,
                       const float dt,
                       const std::uint32_t allocations) : m_integ(tableau, m_buffer), m_dt(dt)
    {
        m_entities.reserve(allocations);
        m_integ.reserve_state(4 * allocations);
    }

    entity2D &engine2D::add(const entity2D &&entity)
    {
        m_buffer.emplace_back(entity.body().pos().x);
        m_buffer.emplace_back(entity.body().pos().y);
        m_buffer.emplace_back(entity.body().vel().x);
        m_buffer.emplace_back(entity.body().vel().y);
        m_entities.emplace_back(entity);
        m_integ.resize_state(m_buffer.size());
        m_entities[m_entities.size() - 1].m_buffer = {&m_buffer, m_buffer.size() - 4};
        return m_entities[m_entities.size() - 1];
    }

    void engine2D::add(const force2D &force) { m_forces.insert(&force); }
    void engine2D::add(const interaction2D &inter) { m_interactions.insert(&inter); }

    bool engine2D::raw_forward()
    {
        DBG_EXIT_IF(m_entities.empty(), "No entities to integrate!\n")
        return m_integ.raw_forward(m_t, m_dt, *this, ode);
    }

    bool engine2D::reiterative_forward()
    {
        DBG_EXIT_IF(m_entities.empty(), "No entities to integrate!\n")
        return m_integ.reiterative_forward(m_t, m_dt, *this, ode);
    }

    bool engine2D::embedded_forward()
    {
        DBG_EXIT_IF(m_entities.empty(), "No entities to integrate!\n")
        return m_integ.embedded_forward(m_t, m_dt, *this, ode);
    }

    void engine2D::until(float time_threshold, bool (engine2D::*forward)())
    {
        while (m_t < time_threshold)
            (this->*forward)();
    }

    float engine2D::elapsed() const { return m_t; }
}