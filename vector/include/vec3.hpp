#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

namespace vec
{
    class vec3
    {
    public:
        double x, y, z;

        vec3() = default;
        vec3(double x, double y, double z);

        double dot(const vec3 &v) const;

        double sq_dist(const vec3 &v) const;
        double dist(const vec3 &v) const;

        double sq_norm() const;
        double norm() const;

        void normalize();
        vec3 normalized() const;

        void xrotate(double angle);
        vec3 xrotated(double angle) const;

        void yrotate(double angle);
        vec3 yrotated(double angle) const;

        void zrotate(double angle);
        vec3 zrotated(double angle) const;

        void rotate(double angle, const vec3 &axis);
        vec3 rotated(double angle, const vec3 &axis) const;

        double angle() const;
        double angle(const vec3 &v) const;

        vec3 cross(const vec3 &v) const;
    };
}

#endif