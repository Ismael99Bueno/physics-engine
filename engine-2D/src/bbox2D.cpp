#include "bbox2D.hpp"

namespace physics
{
    bbox2D::bbox2D(const vec::vec2 &dim,
                   const utils::vec_ptr &buffer) : m_dim(dim), m_buffer(buffer) {}

    void bbox2D::retrieve()
    {
        vec::vec2 pos = {m_buffer[0], m_buffer[1]};
        m_min = pos - m_dim / 2.f;
        m_max = pos + m_dim / 2.f;
    }

    const vec::vec2 &bbox2D::min() const { return m_min; }
    const vec::vec2 &bbox2D::max() const { return m_max; }
}