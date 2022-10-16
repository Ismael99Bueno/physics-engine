#ifndef FORCE2D_HPP
#define FORCE2D_HPP

#include "entity2D.hpp"
#include <unordered_set>
#include <cstdint>

namespace physics
{
    class force2D
    {
    public:
        force2D(std::size_t reserve = 10);
        virtual vec2 acceleration(const body2D &body) const = 0;

    private:
        std::unordered_set<entity2D *> entities;
    };
}

#endif