#include <iostream>
#include "rk_integrator.hpp"
#include "rk_prefab.hpp"
#include <cmath>

std::vector<double> ode(double t, const std::vector<double> &vars)
{
    double x = vars[0], y = vars[1];
    return {x * (1.0 - y), y * (x - 1.0)};
}

int main()
{
    std::vector<double> vars = {4.0, 10.0};
    rk::integrator integ(rk::rkf78, vars, 1e-9);

    double t = 0.0, dt = 0.001;
    const double tf = 100.0;

    std::size_t iters = 0;
    while (t + dt < tf)
    {
        integ.embedded_forward(t, dt, ode);
        std::cout << "t: " << t << " x: " << vars[0] << " y: " << vars[1] << " error: " << integ.error() << "\n";
        iters++;
    }
    dt = tf - t;
    integ.raw_forward(t, dt, ode);
    std::cout << "t: " << t << " x: " << vars[0] << " y: " << vars[1] << " error: " << integ.error() << "\n";
    std::cout << iters << "\n";
}