#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>
#include <cmath>

namespace vec
{
    template <typename T>
    class vec2
    {
    public:
        T x, y;

        vec2() = default;
        vec2(T x, T y);

        T dot(const vec2 &v) const;

        T sq_dist(const vec2 &v) const;
        T dist(const vec2 &v) const;

        T sq_norm() const;
        T norm() const;

        void normalize();
        vec2 normalized() const;

        void rotate(T angle);
        vec2 rotated(T angle) const;

        T angle() const;
        T angle(const vec2 &v) const;
    };

    template <typename T>
    vec2<T>::vec2(T x, T y) : x(x), y(y) {}

    template <typename T>
    T vec2<T>::dot(const vec2 &v) const { return this->x * v.x + this->y * v.y; }

    template <typename T>
    T vec2<T>::sq_dist(const vec2 &v) const { return (*this - v).sq_norm(); }

    template <typename T>
    T vec2<T>::dist(const vec2 &v) const { return (*this - v).norm(); }

    template <typename T>
    T vec2<T>::sq_norm() const { return dot(*this); }

    template <typename T>
    T vec2<T>::norm() const { return sqrt(sq_norm()); }

    template <typename T>
    void vec2<T>::normalize() { *this /= norm(); }

    template <typename T>
    vec2<T> vec2<T>::normalized() const { return *this / norm(); }

    template <typename T>
    void vec2<T>::rotate(T angle) { *this = rotated(angle); }

    template <typename T>
    vec2<T> vec2<T>::rotated(T angle) const
    {
        T x = this->x * cos(angle) - this->y * sin(angle);
        T y = this->x * sin(angle) + this->y * cos(angle);
        return {x, y};
    }

    template <typename T>
    T vec2<T>::angle() const { return atan2(this->y, this->x); }

    template <typename T>
    T vec2<T>::angle(const vec2<T> &v) const { return acos(dot(v) / (norm() * v.norm())); }

    template <typename T>
    vec2<T> operator+(const vec2<T> &v) { return v; }

    template <typename T>
    vec2<T> operator-(const vec2<T> &v) { return {-v.x, -v.y}; }

    template <typename T>
    vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }

    template <typename T>
    vec2<T> operator-(const vec2<T> &lhs, const vec2<T> &rhs) { return lhs + (-rhs); }

    template <typename T>
    vec2<T> operator+(const vec2<T> &lhs, const T &rhs) { return {lhs.x + rhs, lhs.y + rhs}; }

    template <typename T>
    vec2<T> operator-(const vec2<T> &lhs, const T &rhs) { return lhs + (-rhs); }

    template <typename T>
    vec2<T> operator+(const T &lhs, const vec2<T> &rhs) { return rhs + lhs; }

    template <typename T>
    vec2<T> operator-(const T &lhs, const vec2<T> &rhs) { return -rhs + lhs; }

    template <typename T>
    vec2<T> operator+=(vec2<T> &lhs, const vec2<T> &rhs) { return lhs = lhs + rhs; }

    template <typename T>
    vec2<T> operator-=(vec2<T> &lhs, const vec2<T> &rhs) { return lhs = lhs - rhs; }

    template <typename T>
    vec2<T> operator+=(vec2<T> &lhs, const T &rhs) { return lhs = lhs + rhs; }

    template <typename T>
    vec2<T> operator-=(vec2<T> &lhs, const T &rhs) { return lhs = lhs - rhs; }

    template <typename T>
    vec2<T> operator*(const vec2<T> &lhs, const vec2<T> &rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y}; }

    template <typename T>
    vec2<T> operator/(const vec2<T> &lhs, const vec2<T> &rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y}; }

    template <typename T>
    vec2<T> operator*(const vec2<T> &lhs, const T &rhs) { return {lhs.x * rhs, lhs.y * rhs}; }

    template <typename T>
    vec2<T> operator/(const vec2<T> &lhs, const T &rhs) { return {lhs.x / rhs, lhs.y / rhs}; }

    template <typename T>
    vec2<T> operator*(const T &lhs, const vec2<T> &rhs) { return rhs * lhs; }

    template <typename T>
    vec2<T> operator/(const T &lhs, const vec2<T> &rhs) { return lhs / rhs; }

    template <typename T>
    vec2<T> operator*=(vec2<T> &lhs, const vec2<T> &rhs) { return lhs = lhs * rhs; }

    template <typename T>
    vec2<T> operator/=(vec2<T> &lhs, const vec2<T> &rhs) { return lhs = lhs / rhs; }

    template <typename T>
    vec2<T> operator*=(vec2<T> &lhs, const T &rhs) { return lhs = lhs * rhs; }

    template <typename T>
    vec2<T> operator/=(vec2<T> &lhs, const T &rhs) { return lhs = lhs / rhs; }

    template <typename T>
    bool operator==(const vec2<T> &lhs, const vec2<T> &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

    template <typename T>
    bool operator!=(const vec2<T> &lhs, const vec2<T> &rhs) { return !(lhs == rhs); }

    template <typename T>
    std::ostream &operator<<(std::ostream &stream, const vec2<T> &other)
    {
        stream << "x: " << other.x << " y: " << other.y;
        return stream;
    }
}

#endif