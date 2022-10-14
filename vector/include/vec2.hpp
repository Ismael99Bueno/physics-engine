#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>

namespace vec
{
    class vec2
    {
    public:
        double x, y;

        vec2() = default;
        vec2(double x, double y);

        double dot(const vec2 &v) const;

        double sq_dist(const vec2 &v) const;
        double dist(const vec2 &v) const;

        double sq_norm() const;
        double norm() const;

        void normalize();
        vec2 normalized() const;

        void rotate(double angle);
        vec2 rotated(double angle) const;

        double angle() const;
        double angle(const vec2 &v) const;
    };
}

#endif