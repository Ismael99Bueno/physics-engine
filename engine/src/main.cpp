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
    rk::integrator integ(rk::rkf78);

    std::vector<double> vars = {1.0, 0.0};
    double t = 0.0, dt = 0.01;

    std::size_t iters = 0;
    while (t + dt < 10.0)
    {
        vars = integ.raw_forward(t, dt, vars, ode);
        std::cout << "t: " << t << " x: " << vars[0] << " error: " << integ.error() << "\n";
        iters++;
    }
    // vars = integ.raw_forward(t, 10.0 - t, vars, ode);
    // std::cout << "t: " << t << " x: " << vars[0] << " error: " << integ.error() << "\n";
    std::cout << iters << "\n";
}