#ifndef ENTITY2D_HPP
#define ENTITY2D_HPP

#include "body2D.hpp"
#include "vec_ptr.hpp"

namespace physics
{
    class entity2D
    {
    public:
        entity2D() = default;
        entity2D(const body2D &body);

        virtual void retrieve();
        void dispatch() const;

        body2D &body();
        const body2D &body() const;

        bool dynamic() const;
        void dynamic(bool dynamic);

    protected:
        body2D m_body;
        mutable utils::vec_ptr m_buffer;

    private:
        bool m_dynamic = true;

        friend class engine2D;
    };
}

#endif