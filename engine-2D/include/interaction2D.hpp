#ifndef INTERACTION2D_HPP
#define INTERACTION2D_HPP

#include "entity2D.hpp"
#include <unordered_set>
#include <cstdint>

namespace physics
{
    class interaction2D
    {
    public:
        interaction2D(std::size_t allocations = 10);
        virtual vec2 acceleration(const body2D &b1, const body2D &b2) const = 0;

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