#include "vec3.hpp"
#include <cmath>

namespace vec
{
    vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    double vec3::dot(const vec3 &v) const { return x * v.x + y * v.y + z * v.z; }

    double vec3::sq_dist(const vec3 &v) const { return (*this - v).sq_norm(); }

    double vec3::dist(const vec3 &v) const { return (*this - v).norm(); }

    double vec3::sq_norm() const { return dot(*this); }

    double vec3::norm() const { return sqrt(sq_norm()); }

    void vec3::normalize() { *this /= norm(); }

    vec3 vec3::normalized() const { return *this / norm(); }

    void vec3::xrotate(double angle) { *this = yrotated(angle); }

    vec3 vec3::xrotated(double angle) const
    {
        double y = this->y * cos(angle) - this->z * sin(angle);
        double z = this->y * sin(angle) + this->z * cos(angle);
        return {this->x, y, z};
    }

    void vec3::yrotate(double angle) { *this = yrotated(angle); }

    vec3 vec3::yrotated(double angle) const
    {
        double x = this->x * cos(angle) + this->z * sin(angle);
        double z = -this->x * sin(angle) + this->z * cos(angle);
        return {x, this->y, z};
    }

    void vec3::zrotate(double angle) { *this = zrotated(angle); }

    vec3 vec3::zrotated(double angle) const
    {
        double x = this->x * cos(angle) - this->y * sin(angle);
        double y = this->x * sin(angle) + this->y * cos(angle);
        return {x, y, this->z};
    }

    void vec3::rotate(double angle, const vec3 &axis) { *this = rotated(angle, axis); }

    vec3 vec3::rotated(double angle, const vec3 &axis) const
    {
        return *this * (double)cos(angle) + axis.cross(*this) * (double)sin(angle) + axis * dot(axis) * (double)(1.0 - cos(angle));
    }

    vec3 vec3::cross(const vec3 &v) const
    {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    double vec3::angle(const vec3 &v) const { return acos(dot(v) / (norm() * v.norm())); }

    vec3 operator+(const vec3 &v) { return v; }

    vec3 operator-(const vec3 &v) { return {-v.x, -v.y, -v.z}; }

    vec3 operator+(const vec3 &lhs, const vec3 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

    vec3 operator-(const vec3 &lhs, const vec3 &rhs) { return lhs + (-rhs); }

    vec3 operator+(const vec3 &lhs, const double &rhs) { return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs}; }

    vec3 operator-(const vec3 &lhs, const double &rhs) { return lhs + (-rhs); }

    vec3 operator+(const double &lhs, const vec3 &rhs) { return rhs + lhs; }

    vec3 operator-(const double &lhs, const vec3 &rhs) { return -rhs + lhs; }

    vec3 operator+=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs + rhs; }

    vec3 operator-=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs - rhs; }

    vec3 operator+=(vec3 &lhs, const double &rhs) { return lhs = lhs + rhs; }

    vec3 operator-=(vec3 &lhs, const double &rhs) { return lhs = lhs - rhs; }

    vec3 operator*(const vec3 &lhs, const vec3 &rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z}; }

    vec3 operator/(const vec3 &lhs, const vec3 &rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z}; }

    vec3 operator*(const vec3 &lhs, const double &rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; }

    vec3 operator/(const vec3 &lhs, const double &rhs) { return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs}; }

    vec3 operator*(const double &lhs, const vec3 &rhs) { return rhs * lhs; }

    vec3 operator/(const double &lhs, const vec3 &rhs) { return rhs / lhs; }

    vec3 operator*=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs * rhs; }

    vec3 operator/=(vec3 &lhs, const vec3 &rhs) { return lhs = lhs / rhs; }

    vec3 operator*=(vec3 &lhs, const double &rhs) { return lhs = lhs * rhs; }

    vec3 operator/=(vec3 &lhs, const double &rhs) { return lhs = lhs / rhs; }

    bool operator==(const vec3 &lhs, const vec3 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

    bool operator!=(const vec3 &lhs, const vec3 &rhs) { return !(lhs == rhs); }

    std::ostream &operator<<(std::ostream &stream, const vec3 &other)
    {
        stream << "x: " << other.x << " y: " << other.y << " z: " << other.z;
        return stream;
    }
}