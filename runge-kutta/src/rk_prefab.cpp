#include "rk_prefab.hpp"

namespace rk
{
    const tableau rk4 = {
        {0.5, 0.5, 1.0},
        {{0.5},
         {0.0, 0.5},
         {0.0, 0.0, 0.1}},
        {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0},
        4,
        4};
}