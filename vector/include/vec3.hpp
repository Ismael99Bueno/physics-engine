#ifndef VEC3_HPP
#define VEC3_HPP

#include "vec2.hpp"
#include <iostream>

namespace vec
{
    class vec2;
    class vec3
    {
    public:
        double x = 0.0, y = 0.0, z = 0.0;

        vec3() = default;
        vec3(double x, double y, double z);
        vec3(const vec2 &v2);

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

    vec3 operator+(const vec3 &v);

    vec3 operator-(const vec3 &v);

    vec3 operator+(const vec3 &lhs, const vec3 &rhs);

    vec3 operator-(const vec3 &lhs, const vec3 &rhs);

    vec3 operator+(const vec3 &lhs, double rhs);

    vec3 operator-(const vec3 &lhs, double rhs);

    vec3 operator+(double lhs, const vec3 &rhs);

    vec3 operator-(double lhs, const vec3 &rhs);

    vec3 operator+=(vec3 &lhs, const vec3 &rhs);

    vec3 operator-=(vec3 &lhs, const vec3 &rhs);

    vec3 operator+=(vec3 &lhs, double rhs);

    vec3 operator-=(vec3 &lhs, double rhs);

    vec3 operator*(const vec3 &lhs, const vec3 &rhs);

    vec3 operator/(const vec3 &lhs, const vec3 &rhs);

    vec3 operator*(const vec3 &lhs, double rhs);

    vec3 operator/(const vec3 &lhs, double rhs);

    vec3 operator*(double lhs, const vec3 &rhs);

    vec3 operator/(double lhs, const vec3 &rhs);

    vec3 operator*=(vec3 &lhs, const vec3 &rhs);

    vec3 operator/=(vec3 &lhs, const vec3 &rhs);

    vec3 operator*=(vec3 &lhs, double rhs);

    vec3 operator/=(vec3 &lhs, double rhs);

    bool operator==(const vec3 &lhs, const vec3 &rhs);

    bool operator!=(const vec3 &lhs, const vec3 &rhs);

    std::ostream &operator<<(std::ostream &stream, const vec3 &other);
}

#endif