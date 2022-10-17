#ifndef VEC2_HPP
#define VEC2_HPP

#include "vec3.hpp"
#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace vec
{
    class vec3;
    class vec2
    {
    public:
        float x = 0.f, y = 0.f;

        vec2() = default;
        vec2(float x, float y);
        vec2(const vec3 &v3);
        vec2(const sf::Vector2f &v2);

        float dot(const vec2 &v) const;

        float sq_dist(const vec2 &v) const;
        float dist(const vec2 &v) const;

        float sq_norm() const;
        float norm() const;

        void normalize();
        vec2 normalized() const;

        void rotate(float angle);
        vec2 rotated(float angle) const;

        float angle() const;
        float angle(const vec2 &v) const;

        operator vec3() const;
        operator sf::Vector2f() const;
    };

    vec2 operator+(const vec2 &v);

    vec2 operator-(const vec2 &v);

    vec2 operator+(const vec2 &lhs, const vec2 &rhs);

    vec2 operator-(const vec2 &lhs, const vec2 &rhs);

    vec2 operator+(const vec2 &lhs, float rhs);

    vec2 operator-(const vec2 &lhs, float rhs);

    vec2 operator+(float lhs, const vec2 &rhs);

    vec2 operator-(float lhs, const vec2 &rhs);

    vec2 operator+=(vec2 &lhs, const vec2 &rhs);

    vec2 operator-=(vec2 &lhs, const vec2 &rhs);

    vec2 operator+=(vec2 &lhs, float rhs);

    vec2 operator-=(vec2 &lhs, float rhs);

    vec2 operator*(const vec2 &lhs, const vec2 &rhs);

    vec2 operator/(const vec2 &lhs, const vec2 &rhs);

    vec2 operator*(const vec2 &lhs, float rhs);

    vec2 operator/(const vec2 &lhs, float rhs);

    vec2 operator*(float lhs, const vec2 &rhs);

    vec2 operator/(float lhs, const vec2 &rhs);

    vec2 operator*=(vec2 &lhs, const vec2 &rhs);

    vec2 operator/=(vec2 &lhs, const vec2 &rhs);

    vec2 operator*=(vec2 &lhs, float rhs);

    vec2 operator/=(vec2 &lhs, float rhs);

    bool operator==(const vec2 &lhs, const vec2 &rhs);

    bool operator!=(const vec2 &lhs, const vec2 &rhs);

    std::ostream &operator<<(std::ostream &stream, const vec2 &other);
}

#endif