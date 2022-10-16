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
        force2D(std::size_t allocations = 10);
        virtual vec2 acceleration(const body2D &body) const = 0;

        void add(const entity2D &entity);
        void remove(const entity2D &entity);
        bool contains(const entity2D &entity) const;

        std::unordered_set<const entity2D *> &entities();
        const std::unordered_set<const entity2D *> &entities() const;

    private:
        std::unordered_set<const entity2D *> m_entities;
    };
}

#endif