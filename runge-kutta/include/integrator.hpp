#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "tableau.hpp"
#include <cstdint>

namespace rk
{
    class integrator
    {
    private:
        using vector = std::vector<float>;
        using matrix = std::vector<std::vector<float>>;
        using uint8 = std::uint8_t;
        using uint32 = std::uint32_t;

    public:
        integrator() = delete;
        integrator(const tableau &tb,
                   vector &state,
                   float tolerance = 1e-6,
                   float min_dt = 1e-6,
                   float max_dt = 1.f);

        template <typename T>
        bool raw_forward(float &t,
                         float dt,
                         const T &params,
                         vector (*ode)(float, const vector &, const T &));

        template <typename T>
        bool reiterative_forward(float &t,
                                 float &dt,
                                 const T &params,
                                 vector (*ode)(float, const vector &, const T &),
                                 uint8 reiterations = 2);

        template <typename T>
        bool embedded_forward(float &t,
                              float &dt,
                              const T &params,
                              vector (*ode)(float, const vector &, const T &));

        void reserve_state(std::size_t size);
        void resize_state(std::size_t size);

        float tolerance() const;
        float min_dt() const;
        float max_dt() const;
        float error() const;

        void tolerance(float val);
        void min_dt(float val);
        void max_dt(float val);

    private:
        const tableau m_tableau;
        vector &m_state;
        mutable matrix m_kvec;
        float m_tolerance, m_min_dt, m_max_dt, m_error;
        bool m_valid;

        void resize_kvec() const;

        template <typename T>
        void update_kvec(float t,
                         float dt,
                         const vector &state,
                         const T &params,
                         vector (*ode)(float, const vector &, const T &)) const;

        vector generate_solution(float dt,
                                 const vector &state,
                                 const vector &coefs);

        bool dt_too_small(float dt) const;
        bool dt_too_big(float dt) const;
        bool dt_off_bounds(float dt) const;
        static float embedded_error(const vector &sol1, const vector &sol2);
        float reiterative_error(const vector &sol1, const vector &sol2) const;
    };
}

#include "integrator.tpp"

#endif