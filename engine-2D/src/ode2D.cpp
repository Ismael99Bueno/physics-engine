#include "ode2D.hpp"

namespace physics
{
    vec2 apply_force(const entity2D &entity, const force2D &force)
    {
        const body2D &ebody = entity.body();
        const vec2 &pos = ebody.pos(), vel = ebody.pos();
        const body2D body = {pos, vel, ebody.mass(), ebody.charge()};
        return force.acceleration(body);
    }

    std::vector<double> ode(const double t, const std::vector<double> &state, const engine2D &eng)
    {
        std::vector<double> result(state.size(), 0.0);
        for (std::size_t i = 0; i < eng.m_entities.size(); i++)
        {
            const entity2D &entity = eng.m_entities[i];
            std::size_t j = 4 * i;
            result[j + 0] = state[j + 2];
            result[j + 1] = state[j + 3];
            for (const force2D *force : eng.m_forces)
            {
                if (!force->contains(entity))
                    continue;
                vec2 accel = apply_force(entity, *force);
                result[j + 2] += accel.x;
                result[j + 3] += accel.y;
            }
        }
        return result;
    }
}