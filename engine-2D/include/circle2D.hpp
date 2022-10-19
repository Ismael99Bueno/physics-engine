#ifndef CIRCLE2D_HPP
#define CIRCLE2D_HPP

#include "collider2D.hpp"

namespace physics
{
    class circle2D : public collider2D
    {
    public:
        circle2D() = default;
        circle2D(const body2D &body, float radius = 1.f);
        circle2D(const vec::vec2 &dim, float radius = 1.f);
        circle2D(const body2D &body, const vec::vec2 &dim, float radius = 1.f);

        bool overlaps(const circle2D &circle) const; // Make another for polygon

        float radius() const;
        void radius(float radius);

    private:
        float m_radius = 1.f;
    };
}

#endif