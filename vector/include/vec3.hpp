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
        float x = 0.f, y = 0.f, z = 0.f;

        vec3() = default;
        vec3(float x, float y, float z);
        vec3(const vec2 &v2);

        float dot(const vec3 &v) const;

        float sq_dist(const vec3 &v) const;
        float dist(const vec3 &v) const;

        float sq_norm() const;
        float norm() const;

        void normalize();
        vec3 normalized() const;

        void xrotate(float angle);
        vec3 xrotated(float angle) const;

        void yrotate(float angle);
        vec3 yrotated(float angle) const;

        void zrotate(float angle);
        vec3 zrotated(float angle) const;

        void rotate(float angle, const vec3 &axis);
        vec3 rotated(float angle, const vec3 &axis) const;

        float angle() const;
        float angle(const vec3 &v) const;

        vec3 cross(const vec3 &v) const;
    };

    vec3 operator+(const vec3 &v);

    vec3 operator-(const vec3 &v);

    vec3 operator+(const vec3 &lhs, const vec3 &rhs);

    vec3 operator-(const vec3 &lhs, const vec3 &rhs);

    vec3 operator+(const vec3 &lhs, float rhs);

    vec3 operator-(const vec3 &lhs, float rhs);

    vec3 operator+(float lhs, const vec3 &rhs);

    vec3 operator-(float lhs, const vec3 &rhs);

    vec3 operator+=(vec3 &lhs, const vec3 &rhs);

    vec3 operator-=(vec3 &lhs, const vec3 &rhs);

    vec3 operator+=(vec3 &lhs, float rhs);

    vec3 operator-=(vec3 &lhs, float rhs);

    vec3 operator*(const vec3 &lhs, const vec3 &rhs);

    vec3 operator/(const vec3 &lhs, const vec3 &rhs);

    vec3 operator*(const vec3 &lhs, float rhs);

    vec3 operator/(const vec3 &lhs, float rhs);

    vec3 operator*(float lhs, const vec3 &rhs);

    vec3 operator/(float lhs, const vec3 &rhs);

    vec3 operator*=(vec3 &lhs, const vec3 &rhs);

    vec3 operator/=(vec3 &lhs, const vec3 &rhs);

    vec3 operator*=(vec3 &lhs, float rhs);

    vec3 operator/=(vec3 &lhs, float rhs);

    bool operator==(const vec3 &lhs, const vec3 &rhs);

    bool operator!=(const vec3 &lhs, const vec3 &rhs);

    std::ostream &operator<<(std::ostream &stream, const vec3 &other);
}

#endif