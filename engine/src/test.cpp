#include <iostream>
#include "rk_integrator.hpp"
#include "rk_prefab.hpp"
#include <cmath>

std::vector<double> ode(double t, const std::vector<double> &vars)
{
    return {vars[1], -vars[0]};
}

int main()
{
    std::vector<double> vars = {1.0, 0.0};
    rk::integrator integ(rk::rkf78, vars);

    double t = 0.0, dt = 0.001;

    std::size_t iters = 0;
    while (t + dt < 10.0)
    {
        integ.raw_forward(t, dt, ode);
        std::cout << "t: " << t << " x: " << vars[0] << " error: " << integ.error() << "\n";
        iters++;
    }
    std::cout << iters << "\n";
}