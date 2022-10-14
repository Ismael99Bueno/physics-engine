#ifndef VEC2_HPP
#define VEC2_HPP

#include "vec3.hpp"
#include <iostream>

namespace vec
{
    class vec3;
    class vec2
    {
    public:
        double x, y;

        vec2() = default;
        vec2(double x, double y);
        vec2(const vec3 &v3);

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

    vec2 operator+(const vec2 &v);

    vec2 operator-(const vec2 &v);

    vec2 operator+(const vec2 &lhs, const vec2 &rhs);

    vec2 operator-(const vec2 &lhs, const vec2 &rhs);

    vec2 operator+(const vec2 &lhs, double rhs);

    vec2 operator-(const vec2 &lhs, double rhs);

    vec2 operator+(double lhs, const vec2 &rhs);

    vec2 operator-(double lhs, const vec2 &rhs);

    vec2 operator+=(vec2 &lhs, const vec2 &rhs);

    vec2 operator-=(vec2 &lhs, const vec2 &rhs);

    vec2 operator+=(vec2 &lhs, double rhs);

    vec2 operator-=(vec2 &lhs, double rhs);

    vec2 operator*(const vec2 &lhs, const vec2 &rhs);

    vec2 operator/(const vec2 &lhs, const vec2 &rhs);

    vec2 operator*(const vec2 &lhs, double rhs);

    vec2 operator/(const vec2 &lhs, double rhs);

    vec2 operator*(double lhs, const vec2 &rhs);

    vec2 operator/(double lhs, const vec2 &rhs);

    vec2 operator*=(vec2 &lhs, const vec2 &rhs);

    vec2 operator/=(vec2 &lhs, const vec2 &rhs);

    vec2 operator*=(vec2 &lhs, double rhs);

    vec2 operator/=(vec2 &lhs, double rhs);

    bool operator==(const vec2 &lhs, const vec2 &rhs);

    bool operator!=(const vec2 &lhs, const vec2 &rhs);

    std::ostream &operator<<(std::ostream &stream, const vec2 &other);
}

#endif