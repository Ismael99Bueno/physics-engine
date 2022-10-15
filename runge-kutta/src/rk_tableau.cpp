#include "rk_tableau.hpp"

namespace rk
{
    tableau::tableau(vector &&alpha,
                     matrix &&beta,
                     vector &&coefs,
                     const uint8 stage,
                     const uint8 order) : m_alpha(std::move(alpha)),
                                          m_coefs1(std::move(coefs)),
                                          m_beta(std::move(beta)),
                                          m_embedded(false),
                                          m_stage(stage),
                                          m_order(order) {}

    tableau::tableau(vector &&alpha,
                     matrix &&beta,
                     vector &&coefs1,
                     vector &&coefs2,
                     const uint8 stage,
                     const uint8 order) : m_alpha(std::move(alpha)),
                                          m_coefs1(std::move(coefs1)),
                                          m_coefs2(std::move(coefs2)),
                                          m_beta(std::move(beta)),
                                          m_embedded(true),
                                          m_stage(stage),
                                          m_order(order) {}

    const tableau::vector &tableau::alpha() const { return m_alpha; }
    const tableau::matrix &tableau::beta() const { return m_beta; }
    const tableau::vector &tableau::coefs() const { return m_coefs1; }
    const tableau::vector &tableau::coefs1() const { return m_coefs1; }
    const tableau::vector &tableau::coefs2() const
    {
        if (!m_embedded)
            throw "Cannot access to the second set of coefficients if the tableau is not embedded";
        return m_coefs2;
    }
    bool tableau::embedded() const { return m_embedded; }
    tableau::uint8 tableau::stage() const { return m_stage; }
    tableau::uint8 tableau::order() const { return m_order; }

}