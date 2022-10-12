#include <iostream>
#include "rk_integrator.hpp"
#include "rk_prefab.hpp"

std::vector<double> ode(double t, const std::vector<double> &vars)
{
    return {vars[1], -vars[0]};
}

int main()
{
    rk::integrator integ(rk::rk4);
    std::vector<double> vars = {1.0, 0.0};
    double t = 0.0;

    while (t < 10.0)
    {
        vars = integ.forward(t, 0.01, vars, ode);
        std::cout << "t: " << t << " x: " << vars[0] << std::endl;
    }
}