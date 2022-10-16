#include <iostream>
#include "prefab.hpp"
#include "engine2D.hpp"
#include "vec_ptr.hpp"
#include "vec2.hpp"
#include "force2D.hpp"
#include <cmath>

using namespace physics;

class gravity : public force2D
{
    vec2 acceleration(const body2D &body) const override
    {
        return vec2(0.0, -1.0);
    }
};

int main()
{
    engine2D eng(rk::rk4);

    gravity grav;
    entity2D &e = eng.add();
    grav.add(e);
    eng.add(grav);
    while (eng.elapsed() < 1.0)
    {
        eng.raw_forward();
        e.retrieve();
        std::cout << e.body().pos() << " " << e.body().vel() << "\n";
    }
}