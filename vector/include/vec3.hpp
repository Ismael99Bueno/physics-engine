#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

namespace vec
{
    template <typename T>
    class vec3
    {
    public:
        T x, y, z;

        vec3() = default;
        vec3(T x, T y, T z);

        T dot(const vec3 &v) const;

        T sq_dist(const vec3 &v) const;
        T dist(const vec3 &v) const;

        T sq_norm() const;
        T norm() const;

        void normalize();
        vec3 normalized() const;

        void xrotate(T angle);
        vec3 xrotated(T angle) const;

        void yrotate(T angle);
        vec3 yrotated(T angle) const;

        void zrotate(T angle);
        vec3 zrotated(T angle) const;

        void rotate(T angle, const vec3 &axis);
        vec3 rotated(T angle, const vec3 &axis) const;

        T angle() const;
        T angle(const vec3 &v) const;

        vec3 cross(const vec3 &v) const;
    };

    template <typename T>
    vec3<T>::vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    template <typename T>
    T vec3<T>::dot(const vec3 &v) const { return x * v.x + y * v.y + z * v.z; }

    template <typename T>
    T vec3<T>::sq_dist(const vec3 &v) const { return (*this - v).sq_norm(); }

    template <typename T>
    T vec3<T>::dist(const vec3 &v) const { return (*this - v).norm(); }

    template <typename T>
    T vec3<T>::sq_norm() const { return dot(*this); }

    template <typename T>
    T vec3<T>::norm() const { return sqrt(sq_norm()); }

    template <typename T>
    void vec3<T>::normalize() { *this /= norm(); }

    template <typename T>
    vec3<T> vec3<T>::normalized() const { return *this / norm(); }

    template <typename T>
    void vec3<T>::xrotate(T angle) { *this = yrotated(angle); }

    template <typename T>
    vec3<T> vec3<T>::xrotated(T angle) const
    {
        T y = this->y * cos(angle) - this->z * sin(angle);
        T z = this->y * sin(angle) + this->z * cos(angle);
        return {this->x, y, z};
    }

    template <typename T>
    void vec3<T>::yrotate(T angle) { *this = yrotated(angle); }

    template <typename T>
    vec3<T> vec3<T>::yrotated(T angle) const
    {
        T x = this->x * cos(angle) + this->z * sin(angle);
        T z = -this->x * sin(angle) + this->z * cos(angle);
        return {x, this->y, z};
    }

    template <typename T>
    void vec3<T>::zrotate(T angle) { *this = zrotated(angle); }

    template <typename T>
    vec3<T> vec3<T>::zrotated(T angle) const
    {
        T x = this->x * cos(angle) - this->y * sin(angle);
        T y = this->x * sin(angle) + this->y * cos(angle);
        return {x, y, this->z};
    }

    template <typename T>
    void vec3<T>::rotate(T angle, const vec3<T> &axis) { *this = rotated(angle, axis); }

    template <typename T>
    vec3<T> vec3<T>::rotated(T angle, const vec3<T> &axis) const
    {
        return *this * (T)cos(angle) + axis.cross(*this) * (T)sin(angle) + axis * dot(axis) * (T)(1.0 - cos(angle));
    }

    template <typename T>
    vec3<T> vec3<T>::cross(const vec3<T> &v) const
    {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    template <typename T>
    T vec3<T>::angle(const vec3<T> &v) const { return acos(dot(v) / (norm() * v.norm())); }

    template <typename T>
    vec3<T> operator+(const vec3<T> &v) { return v; }

    template <typename T>
    vec3<T> operator-(const vec3<T> &v) { return {-v.x, -v.y, -v.z}; }

    template <typename T>
    vec3<T> operator+(const vec3<T> &lhs, const vec3<T> &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

    template <typename T>
    vec3<T> operator-(const vec3<T> &lhs, const vec3<T> &rhs) { return lhs + (-rhs); }

    template <typename T>
    vec3<T> operator+(const vec3<T> &lhs, const T &rhs) { return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs}; }

    template <typename T>
    vec3<T> operator-(const vec3<T> &lhs, const T &rhs) { return lhs + (-rhs); }

    template <typename T>
    vec3<T> operator+(const T &lhs, const vec3<T> &rhs) { return rhs + lhs; }

    template <typename T>
    vec3<T> operator-(const T &lhs, const vec3<T> &rhs) { return -rhs + lhs; }

    template <typename T>
    vec3<T> operator+=(vec3<T> &lhs, const vec3<T> &rhs) { return lhs = lhs + rhs; }

    template <typename T>
    vec3<T> operator-=(vec3<T> &lhs, const vec3<T> &rhs) { return lhs = lhs - rhs; }

    template <typename T>
    vec3<T> operator+=(vec3<T> &lhs, const T &rhs) { return lhs = lhs + rhs; }

    template <typename T>
    vec3<T> operator-=(vec3<T> &lhs, const T &rhs) { return lhs = lhs - rhs; }

    template <typename T>
    vec3<T> operator*(const vec3<T> &lhs, const vec3<T> &rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z}; }

    template <typename T>
    vec3<T> operator/(const vec3<T> &lhs, const vec3<T> &rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z}; }

    template <typename T>
    vec3<T> operator*(const vec3<T> &lhs, const T &rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; }

    template <typename T>
    vec3<T> operator/(const vec3<T> &lhs, const T &rhs) { return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs}; }

    template <typename T>
    vec3<T> operator*(const T &lhs, const vec3<T> &rhs) { return rhs * lhs; }

    template <typename T>
    vec3<T> operator/(const T &lhs, const vec3<T> &rhs) { return rhs / lhs; }

    template <typename T>
    vec3<T> operator*=(vec3<T> &lhs, const vec3<T> &rhs) { return lhs = lhs * rhs; }

    template <typename T>
    vec3<T> operator/=(vec3<T> &lhs, const vec3<T> &rhs) { return lhs = lhs / rhs; }

    template <typename T>
    vec3<T> operator*=(vec3<T> &lhs, const T &rhs) { return lhs = lhs * rhs; }

    template <typename T>
    vec3<T> operator/=(vec3<T> &lhs, const T &rhs) { return lhs = lhs / rhs; }

    template <typename T>
    bool operator==(const vec3<T> &lhs, const vec3<T> &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

    template <typename T>
    bool operator!=(const vec3<T> &lhs, const vec3<T> &rhs) { return !(lhs == rhs); }

    template <typename T>
    std::ostream &operator<<(std::ostream &stream, const vec3<T> &other)
    {
        stream << "x: " << other.x << " y: " << other.y << " z: " << other.z;
        return stream;
    }
}

#endif