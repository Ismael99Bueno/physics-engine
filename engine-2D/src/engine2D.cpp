#include "engine2D.hpp"
#include "debug.h"

namespace physics
{
    std::vector<double> ode(const double t, const std::vector<double> &state, const engine2D &eng)
    {
        std::vector<double> result(state.size(), 0.0);
        for (std::size_t i = 0; i < eng.m_entities.size(); i++)
        {
            std::size_t j = 4 * i;
            result[j + 0] = state[j + 2];
            result[j + 1] = state[j + 3];
        }
        return result;
    }

    engine2D::engine2D(const rk::tableau &tableau,
                       const double dt,
                       const std::uint32_t allocations) : m_integ(tableau, m_buffer), m_dt(dt)
    {
        m_entities.reserve(allocations);
        m_integ.reserve_state(4 * allocations);
    }

    void engine2D::add(std::size_t amount)
    {
        DBG_LOG_IF(amount < 1, "Adding 0 entities...\n")
        for (std::size_t i = 0; i < amount; i++)
            add(entity2D());
    }

    void engine2D::add(const entity2D &entity)
    {
        m_buffer.emplace_back(entity.body().pos().x);
        m_buffer.emplace_back(entity.body().pos().y);
        m_buffer.emplace_back(entity.body().vel().x);
        m_buffer.emplace_back(entity.body().vel().y);
        m_entities.emplace_back(entity);
        m_integ.resize_state(m_buffer.size());
        m_entities[m_entities.size() - 1].m_buffer = {&m_buffer, m_buffer.size() - 4};
    }

    void engine2D::add(const entity2D &entity, std::size_t amount)
    {
        DBG_LOG_IF(amount < 1, "Adding 0 entities...\n")
        for (std::size_t i = 0; i < amount; i++)
            add(entity);
    }

    void engine2D::add(const std::vector<entity2D> &entities)
    {
        for (const entity2D &entity : entities)
            add(entity);
    }

    bool engine2D::raw_forward()
    {
        DBG_EXIT_IF(m_entities.empty(), "No entities to integrate!\n")
        m_integ.raw_forward(m_t, m_dt, *this, ode);
        return m_integ.valid();
    }

    void engine2D::until(double time_threshold, bool (engine2D::*forward)())
    {
        while (m_t < time_threshold)
            (this->*forward)();
    }
}