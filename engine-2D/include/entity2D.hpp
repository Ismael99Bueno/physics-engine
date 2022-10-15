#ifndef ENTITY2D_HPP
#define ENTITY2D_HPP

#include "body2D.hpp"

namespace physics
{
    class entity2D
    {
    public:
        entity2D() = default;
        entity2D(const body2D &body);

        void retrieve();
        void dispatch();

        body2D &body();
        const body2D &body() const;

    private:
        body2D m_body;
        mutable double *m_buffer = nullptr;
    };
}

#endif