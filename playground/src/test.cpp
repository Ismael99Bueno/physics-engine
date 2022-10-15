#include <iostream>
#include "entity2D.hpp"
#include <cmath>

int main()
{
    physics::entity2D e = {{{1.0, 2.0}, {1.0, 1.0}}};
    e.retrieve();
    std::cout << e.body().vel() << "\n";
}