#include <iostream>
#include "integrator.hpp"
#include "prefab.hpp"
#include <cmath>

struct lv
{
    double alpha, beta, gamma, delta;
};

std::vector<double> ode(double t, const std::vector<double> &vars, const lv &params)
{
    double x = vars[0], y = vars[1];
    return {x * (params.alpha - params.beta * y), y * (params.gamma * x - params.delta)};
}

int main()
{
    std::vector<double> vars = {4.0, 10.0};
    rk::integrator integ(rk::rk38, vars, 1e-12);
    lv prm = {2.0, 1.0, 1.0, 1.0};

    double t = 0.0, dt = 0.001;
    const double tf = 10.0;

    std::size_t iters = 0;
    while (t + dt < tf)
    {
        integ.reiterative_forward(t, dt, prm, ode);
        std::cout << "t: " << t << " x: " << vars[0] << " y: " << vars[1] << " error: " << integ.error() << "\n";
        iters++;
    }
    dt = tf - t;
    integ.raw_forward(t, dt, prm, ode);
    std::cout << "t: " << t << " x: " << vars[0] << " y: " << vars[1] << " error: " << integ.error() << "\n";
    std::cout << iters << "\n";
}