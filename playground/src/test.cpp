#include <iostream>
#include "prefab.hpp"
#include "engine2D.hpp"
#include <cmath>

using namespace physics;

int main()
{
    engine2D eng(rk::rk4);
    entity2D e1 = body2D({1.0, 2.0}, {3.0, -1.0}), e2 = body2D({-1.0, 2.0}, {-3.0, 1.2});
    eng.add({e1, e2});
    eng.until(10.0, &engine2D::raw_forward);
}