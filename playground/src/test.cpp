#include <iostream>
#include "prefab.hpp"
#include "engine2D.hpp"
#include "vec_ptr.hpp"
#include "vec2.hpp"
#include "force2D.hpp"
#include "interaction2D.hpp"
#include <cmath>

using namespace physics;

class gravity : public force2D
{
    vec2 acceleration(const body2D &body) const override
    {
        return vec2(0.0, -1.0);
    }
};

class gravitation : public interaction2D
{
    vec2 acceleration(const body2D &b1, const body2D &b2) const override
    {
        return (b2.pos() - b1.pos()).normalized() * (b2.mass() / b1.pos().sq_dist(b2.pos()));
    }
};

int main()
{
    engine2D eng(rk::rk4);
    entity2D &e1 = eng.add(), &e2 = eng.add();
    e1.body().pos({1.0, 0.0});
    e1.body().vel({0.0, -1.0});
    e1.dispatch();

    gravitation grav;

    grav.add(e1);
    grav.add(e2);
    eng.add(grav);
    while (eng.elapsed() < 1.0)
    {
        eng.raw_forward();
        e1.retrieve();
        std::cout << e1.body().pos() << " " << e1.body().vel() << "\n";
    }
}