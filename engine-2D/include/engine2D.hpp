#ifndef ENGINE2D_HPP
#define ENGINE2D_HPP

#include "integrator.hpp"
#include "entity2D.hpp"
#include "force2D.hpp"
#include "interaction2D.hpp"
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
                 float dt = .01f,
                 std::uint32_t allocations = 1000);

        entity2D &add(const entity2D &&entity = entity2D()); // CHECK DEFAULT!! Maybe it does not initialize to zero
        void add(const force2D &force);
        void add(const interaction2D &inter);

        bool raw_forward();
        bool reiterative_forward();
        bool embedded_forward();
        void until(float time_threshold, bool (engine2D::*forward)());

        float elapsed() const;

    private:
        std::vector<entity2D> m_entities;
        std::vector<float> m_buffer;

        std::unordered_set<const force2D *> m_forces;
        std::unordered_set<const interaction2D *> m_interactions;

        rk::integrator m_integ;
        float m_dt, m_t = 0.f;

        friend std::vector<float> ode(float t, const std::vector<float> &state, const engine2D &eng);
    };
}

#endif