#ifndef RK_TABLEAU_HPP
#define RK_TABLEAU_HPP

#include <vector>
#include <cstdint>

namespace rk
{
    class tableau
    {
    private:
        using vector1d = std::vector<double>;
        using vector2d = std::vector<std::vector<double>>;
        using int8 = std::uint8_t;

    public:
        tableau() = delete;

        tableau(const vector1d &alpha,
                const vector2d &beta,
                const vector1d &coefs,
                int8 stage,
                int8 order);

        tableau(const vector1d &alpha,
                const vector2d &beta,
                const vector1d &coefs1,
                const vector1d &coefs2,
                int8 stage,
                int8 order);

        tableau(vector1d &&alpha,
                vector2d &&beta,
                vector1d &&coefs,
                int8 stage,
                int8 order);

        tableau(vector1d &&alpha,
                vector2d &&beta,
                vector1d &&coefs1,
                vector1d &&coefs2,
                int8 stage,
                int8 order);

        const vector1d &alpha() const;
        const vector2d &beta() const;
        const vector1d &coefs() const;
        const vector1d &coefs1() const;
        const vector1d &coefs2() const;
        bool embedded() const;
        int8 stage() const;
        int8 order() const;

    private:
        vector1d m_alpha, m_coefs1, m_coefs2;
        vector2d m_beta;
        bool m_embedded;
        int8 m_stage, m_order;
    };
}

#endif