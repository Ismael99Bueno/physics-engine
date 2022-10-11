#include "butcher_tableau.hpp"

namespace rk
{
    tableau::tableau(const vector1d &alpha,
                     const vector2d &beta,
                     const vector1d &coefs,
                     int8 stage,
                     int8 order) : m_alpha(alpha),
                                   m_coefs1(coefs),
                                   m_beta(beta),
                                   m_embedded(false),
                                   m_stage(stage),
                                   m_order(order) {}

    tableau::tableau(const vector1d &alpha,
                     const vector2d &beta,
                     const vector1d &coefs1,
                     const vector1d &coefs2,
                     int8 stage,
                     int8 order) : m_alpha(alpha),
                                   m_coefs1(coefs1),
                                   m_coefs2(coefs1),
                                   m_beta(beta),
                                   m_embedded(true),
                                   m_stage(stage),
                                   m_order(order) {}

    tableau::tableau(vector1d &&alpha,
                     vector2d &&beta,
                     vector1d &&coefs,
                     int8 stage,
                     int8 order) : m_alpha(std::move(alpha)),
                                   m_coefs1(std::move(coefs)),
                                   m_beta(std::move(beta)),
                                   m_embedded(false),
                                   m_stage(stage),
                                   m_order(order) {}

    tableau::tableau(vector1d &&alpha,
                     vector2d &&beta,
                     vector1d &&coefs1,
                     vector1d &&coefs2,
                     int8 stage,
                     int8 order) : m_alpha(std::move(alpha)),
                                   m_coefs1(std::move(coefs1)),
                                   m_coefs2(std::move(coefs2)),
                                   m_beta(std::move(beta)),
                                   m_embedded(true),
                                   m_stage(stage),
                                   m_order(order) {}

    const tableau::vector1d &tableau::alpha() const { return m_alpha; }
    const tableau::vector2d &tableau::beta() const { return m_beta; }
    const tableau::vector1d &tableau::coefs() const { return m_coefs1; }
    const tableau::vector1d &tableau::coefs1() const { return m_coefs1; }
    const tableau::vector1d &tableau::coefs2() const
    {
        if (!m_embedded)
            throw "Cannot access to the second set of coefficients if the tableau is not embedded";
        return m_coefs2;
    }
    bool tableau::embedded() const { return m_embedded; }
    tableau::int8 tableau::stage() const { return m_stage; }
    tableau::int8 tableau::order() const { return m_order; }

}