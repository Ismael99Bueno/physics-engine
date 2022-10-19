#ifndef BBOX2D_HPP
#define BBOX2D_HPP

#include "vec2.hpp"
#include "vec_ptr.hpp"

namespace physics
{
    class bbox2D
    {
    public:
        bbox2D() = delete;
        bbox2D(const vec::vec2 &dim, const utils::vec_ptr &buffer);

        void retrieve();
        bool overlaps(const bbox2D &bbox) const;

        const vec::vec2 &min() const;
        const vec::vec2 &max() const;

    private:
        vec::vec2 m_min, m_max, m_dim;
        const utils::vec_ptr &m_buffer;
    };
}

#endif