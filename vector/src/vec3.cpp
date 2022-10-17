#include "vec3.hpp"
#include <cmath>

namespace vec
{
    vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3::vec3(const vec2 &v2) : x(v2.x), y(v2.y), z(0.f) {}

    float vec3::dot(const vec3 &v) const { return x * v.x + y * v.y + z * v.z; }

    float vec3::sq_dist(const vec3 &v) const { return (*this - v).sq_norm(); }

    float vec3::dist(const vec3 &v) const { return (*this - v).norm(); }

    float vec3::sq_norm() const { return dot(*this); }

    float vec3::norm() const { return sqrt(sq_norm()); }

    void vec3::normalize() { *this /= norm(); }

    vec3 vec3::normalized() const { return *this / norm(); }

    void vec3::xrotate(float angle) { *this = yrotated(angle); }

    vec3 vec3::xrotated(float angle) const
    {
        float y = this->y * cos(angle) - this->z * sin(angle);
        float z = this->y * sin(angle) + this->z * cos(angle);
        return {this->x, y, z};
    }

    void vec3::yrotate(float angle) { *this = yrotated(angle); }

    vec3 vec3::yrotated(float angle) const
    {
        float x = this->x * cos(angle) + this->z * sin(angle);
        float z = -this->x * sin(angle) + this->z * cos(angle);
        return {x, this->y, z};
    }

    void vec3::zrotate(float angle) { *this = zrotated(angle); }

    vec3 vec3::zrotated(float angle) const
    {
        float x = this->x * cos(angle) - this->y * sin(angle);
        float y = this->x * sin(angle) + this->y * cos(angle);
        return {x, y, this->z};
    }

    void vec3::rotate(float angle, const vec3 &axis) { *this = rotated(angle, axis); }

    vec3 vec3::rotated(float angle, const vec3 &axis) const
    {
        return *this * (float)cos(angle) + axis.cross(*this) * (float)sin(angle) + axis * dot(axis) * (float)(1.f - cos(angle));
    }

    vec3 vec3::cross(const vec3 &v) const
    {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    float vec3::angle(const vec3 &v) const { return acos(dot(v) / (norm() * v.norm())); }

    vec3 operator+(const vec3 &v) { return v; }

    vec3 operator-(const vec3 &v) { return {-v.x, -v.y, -v.z}; }

    vec3 operator+(const vec3 &lhs, const vec3 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

    vec3 operator-(const vec3 &lhs, const vec3 &rhs) { return lhs + (-rhs); }

    vec3 operator+(const vec3 &lhs, const float rhs) { return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs}; }

    vec3 operator-(const vec3 &lhs, const float rhs) { return lhs + (-rhs); }

    vec3 operator+(const float lhs, const vec3 &rhs) { return rhs + lhs; }

    vec3 operator-(const float lhs, const vec3 &rhs) { return -rhs + lhs; }

    vec3 operator+=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs + rhs; }

    vec3 operator-=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs - rhs; }

    vec3 operator+=(vec3 &lhs, const float rhs) { return lhs = lhs + rhs; }

    vec3 operator-=(vec3 &lhs, const float rhs) { return lhs = lhs - rhs; }

    vec3 operator*(const vec3 &lhs, const vec3 &rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z}; }

    vec3 operator/(const vec3 &lhs, const vec3 &rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z}; }

    vec3 operator*(const vec3 &lhs, const float rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; }

    vec3 operator/(const vec3 &lhs, const float rhs) { return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs}; }

    vec3 operator*(const float lhs, const vec3 &rhs) { return rhs * lhs; }

    vec3 operator/(const float lhs, const vec3 &rhs) { return rhs / lhs; }

    vec3 operator*=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs * rhs; }

    vec3 operator/=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs / rhs; }

    vec3 operator*=(vec3 &lhs, const float rhs) { return lhs = lhs * rhs; }

    vec3 operator/=(vec3 &lhs, const float rhs) { return lhs = lhs / rhs; }

    bool operator==(const vec3 &lhs, const vec3 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

    bool operator!=(const vec3 &lhs, const vec3 &rhs) { return !(lhs == rhs); }

    std::ostream &operator<<(std::ostream &stream, const vec3 &other)
    {
        stream << "x: " << other.x << " y: " << other.y << " z: " << other.z;
        return stream;
    }
}