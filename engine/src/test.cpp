#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"

int main()
{
    std::cout << "Hello Test\n";
    vec::vec2 v2(1.0, 2.0);
    vec::vec3 v3 = v2;
    std::cout << v3 + 3.8756 << "\n";
}