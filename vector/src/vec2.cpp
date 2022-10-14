#include "vec2.hpp"
#include <cmath>

namespace vec
{
    vec2::vec2(double x, double y) : x(x), y(y) {}

    double vec2::dot(const vec2 &v) const { return this->x * v.x + this->y * v.y; }

    double vec2::sq_dist(const vec2 &v) const { return (*this - v).sq_norm(); }

    double vec2::dist(const vec2 &v) const { return (*this - v).norm(); }

    double vec2::sq_norm() const { return dot(*this); }

    double vec2::norm() const { return sqrt(sq_norm()); }

    void vec2::normalize() { *this /= norm(); }

    vec2 vec2::normalized() const { return *this / norm(); }

    void vec2::rotate(double angle) { *this = rotated(angle); }

    vec2 vec2::rotated(double angle) const
    {
        double x = this->x * cos(angle) - this->y * sin(angle);
        double y = this->x * sin(angle) + this->y * cos(angle);
        return {x, y};
    }

    double vec2::angle() const { return atan2(this->y, this->x); }

    double vec2::angle(const vec2 &v) const { return acos(dot(v) / (norm() * v.norm())); }

    vec2 operator+(const vec2 &v) { return v; }

    vec2 operator-(const vec2 &v) { return {-v.x, -v.y}; }

    vec2 operator+(const vec2 &lhs, const vec2 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }

    vec2 operator-(const vec2 &lhs, const vec2 &rhs) { return lhs + (-rhs); }

    vec2 operator+(const vec2 &lhs, const double &rhs) { return {lhs.x + rhs, lhs.y + rhs}; }

    vec2 operator-(const vec2 &lhs, const double &rhs) { return lhs + (-rhs); }

    vec2 operator+(const double &lhs, const vec2 &rhs) { return rhs + lhs; }

    vec2 operator-(const double &lhs, const vec2 &rhs) { return -rhs + lhs; }

    vec2 operator+=(vec2 &lhs, const vec2 &rhs) { return lhs = lhs + rhs; }

    vec2 operator-=(vec2 &lhs, const vec2 &rhs) { return lhs = lhs - rhs; }

    vec2 operator+=(vec2 &lhs, const double &rhs) { return lhs = lhs + rhs; }

    vec2 operator-=(vec2 &lhs, const double &rhs) { return lhs = lhs - rhs; }

    vec2 operator*(const vec2 &lhs, const vec2 &rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y}; }

    vec2 operator/(const vec2 &lhs, const vec2 &rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y}; }

    vec2 operator*(const vec2 &lhs, const double &rhs) { return {lhs.x * rhs, lhs.y * rhs}; }

    vec2 operator/(const vec2 &lhs, const double &rhs) { return {lhs.x / rhs, lhs.y / rhs}; }

    vec2 operator*(const double &lhs, const vec2 &rhs) { return rhs * lhs; }

    vec2 operator/(const double &lhs, const vec2 &rhs) { return lhs / rhs; }

    vec2 operator*=(vec2 &lhs, const vec2 &rhs) { return lhs = lhs * rhs; }

    vec2 operator/=(vec2 &lhs, const vec2 &rhs) { return lhs = lhs / rhs; }

    vec2 operator*=(vec2 &lhs, const double &rhs) { return lhs = lhs * rhs; }

    vec2 operator/=(vec2 &lhs, const double &rhs) { return lhs = lhs / rhs; }

    bool operator==(const vec2 &lhs, const vec2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

    bool operator!=(const vec2 &lhs, const vec2 &rhs) { return !(lhs == rhs); }

    std::ostream &operator<<(std::ostream &stream, const vec2 &other)
    {
        stream << "x: " << other.x << " y: " << other.y;
        return stream;
    }
}