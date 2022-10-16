#include "entity2D.hpp"
#include "debug.h"

namespace physics
{
    entity2D::entity2D(const body2D &body) : m_body(body) {}

    void entity2D::retrieve()
    {
        DBG_EXIT_IF(!m_buffer, "Entity buffer not initialized, likely due to not being part of any engine.\n")
        m_body.pos({m_buffer[0], m_buffer[1]});
        m_body.vel({m_buffer[2], m_buffer[3]});
    }

    void entity2D::dispatch() const
    {
        DBG_EXIT_IF(!m_buffer, "Entity buffer not initialized, likely due to not being part of any engine.\n")
        m_buffer[0] = m_body.pos().x;
        m_buffer[1] = m_body.pos().y;
        m_buffer[2] = m_body.vel().x;
        m_buffer[3] = m_body.vel().y;
    }

    body2D &entity2D::body() { return m_body; }
    const body2D &entity2D::body() const { return m_body; }

    bool entity2D::dynamic() const { return m_dynamic; }
    void entity2D::dynamic(bool dynamic) { m_dynamic = dynamic; }
}