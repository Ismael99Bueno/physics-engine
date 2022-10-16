#ifndef ENGINE2D_HPP
#define ENGINE2D_HPP

#include "integrator.hpp"
#include "entity2D.hpp"
#include "force2D.hpp"
#include <unordered_set>
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

        entity2D &add(const entity2D &&entity = entity2D()); // CHECK DEFAULT!! Maybe it does not initialize to zero
        void add(const force2D &force);

        bool raw_forward();
        void until(double time_threshold, bool (engine2D::*forward)());

        double elapsed() const;

    private:
        std::vector<entity2D> m_entities;
        std::vector<double> m_buffer;
        std::unordered_set<const force2D *> m_forces;

        rk::integrator m_integ;
        double m_dt, m_t = 0.0;

        friend std::vector<double> ode(double t, const std::vector<double> &state, const engine2D &eng);
    };
}

#endif