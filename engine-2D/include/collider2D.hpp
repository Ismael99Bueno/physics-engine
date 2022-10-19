#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include "entity2D.hpp"
#include "bbox2D.hpp"

namespace physics
{
    class collider2D : public entity2D // Maybe collider2D returns as vertices the bounding box
    {
    public:
        collider2D() = default;
        collider2D(const body2D &body);
        collider2D(const vec::vec2 &dim);
        collider2D(const body2D &body, const vec::vec2 &dim);

        void retrieve() override;

        const bbox2D &bbox() const;

    protected:
        bbox2D m_bbox = {{1.f, 1.f}, m_buffer};
    };
}

#endif