#include "rk_integrator.hpp"
#include "debug.h"
#include <cmath>

#define SAFETY_FACTOR 0.85
#define TOL_PART 256.0

namespace rk
{
    integrator::integrator(const tableau &tb,
                           vector &state,
                           const double tolerance,
                           const double min_dt,
                           const double max_dt) : m_tableau(tb),
                                                  m_state(state),
                                                  m_tolerance(tolerance),
                                                  m_min_dt(min_dt),
                                                  m_max_dt(max_dt),
                                                  m_error(0.0),
                                                  m_valid(true) { resize_kvec(); }

    void integrator::resize_kvec() const
    {
        m_kvec.resize(m_tableau.stage());
        for (vector &v : m_kvec)
            v.resize(m_state.size());
    }

    integrator::vector integrator::generate_solution(const double dt,
                                                     const vector &state,
                                                     const vector &coefs) const
    {
        vector sol;
        sol.reserve(state.size());
        for (std::size_t j = 0; j < state.size(); j++)
        {
            double sum = 0.0;
            for (uint8 i = 0; i < m_tableau.stage(); i++)
                sum += coefs[i] * m_kvec[i][j];
            m_valid &= !isnan(sum);
            DBG_LOG_IF(!m_valid, "NaN encountered when computing runge-kutta solution.\n")
            sol.emplace_back(state[j] + sum * dt);
        }
        return sol;
    }

    static std::uint32_t ipow(std::uint32_t base, std::uint32_t exponent)
    {
        int result = 1;
        for (;;)
        {
            if (exponent & 1)
                result *= base;
            exponent >>= 1;
            if (!exponent)
                break;
            base *= base;
        }

        return result;
    }

    bool integrator::dt_too_small(const double dt) const { return dt < m_min_dt; }
    bool integrator::dt_too_big(const double dt) const { return dt > m_max_dt; }
    bool integrator::dt_off_bounds(const double dt) const { return dt_too_small(dt) || dt_too_big(dt); }

    double integrator::embedded_error(const vector &sol1, const vector &sol2)
    {
        double result = 0.0;
        for (std::size_t i = 0; i < sol1.size(); i++)
            result += (sol1[i] - sol2[i]) * (sol1[i] - sol2[i]);
        return result;
    }

    double integrator::reiterative_error(const vector &sol1, const vector &sol2) const
    {
        const uint32 coeff = ipow(2, m_tableau.order()) - 1;
        return embedded_error(sol1, sol2) / coeff;
    }

    double integrator::tolerance() const { return m_tolerance; }
    double integrator::min_dt() const { return m_min_dt; }
    double integrator::max_dt() const { return m_max_dt; }
    double integrator::error() const { return m_error; }
    bool integrator::valid() const { return m_valid; }

    void integrator::tolerance(const double val) { m_tolerance = val; }
    void integrator::min_dt(const double val) { m_min_dt = val; }
    void integrator::max_dt(const double val) { m_max_dt = val; }
}