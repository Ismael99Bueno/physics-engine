#ifndef ENGINE2D_HPP
#define ENGINE2D_HPP

#include "integrator.hpp"
#include "entity2D.hpp"
#include <cstdint>
#include <vector>

namespace physics
{
    class engine2D
    {
    public:
        engine2D() = delete;
        engine2D(const rk::tableau &tableau,
                 double dt = 0.001,
                 std::uint32_t allocations = 1000);

        void add(const entity2D &entity);
        void add(const std::vector<entity2D> &entities);

    private:
        std::vector<entity2D> m_entities;
        std::vector<double> m_buffer;
        rk::integrator m_integ;
        double m_dt;
    };
}

#endif