#include "ode2D.hpp"

namespace physics
{
    std::vector<double> ode(const double t, const std::vector<double> &state, const engine2D &eng)
    {
        std::vector<double> result(state.size(), 0.0);
        for (std::size_t i = 0; i < eng.m_entities.size(); i++)
        {
            const entity2D &entity1 = eng.m_entities[i];
            std::size_t j = 4 * i;
            result[j + 0] = state[j + 2];
            result[j + 1] = state[j + 3];
            for (const force2D *force : eng.m_forces)
            {
                if (!force->contains(entity1))
                    continue;
                vec2 pos = {state[j + 0], state[j + 1]}, vel = {state[j + 2], state[j + 3]};
                body2D body = {pos, vel, entity1.body().mass(), entity1.body().charge()};
                vec2 accel = force->acceleration(body);
                result[j + 2] += accel.x;
                result[j + 3] += accel.y;
            }

            for (const interaction2D *inter : eng.m_interactions)
            {
                if (!inter->contains(entity1))
                    continue;
                for (std::size_t k = 0; k < eng.m_entities.size(); k++)
                {
                    const entity2D &entity2 = eng.m_entities[k];
                    if (&entity1 == &entity2 || !inter->contains(entity2))
                        continue;
                    std::size_t l = 4 * k;
                    vec2 pos1 = {state[j + 0], state[j + 1]}, vel1 = {state[j + 2], state[j + 3]};
                    vec2 pos2 = {state[l + 0], state[l + 1]}, vel2 = {state[l + 2], state[l + 3]};
                    body2D body1 = {pos1, vel1, entity1.body().mass(), entity1.body().charge()};
                    body2D body2 = {pos2, vel2, entity2.body().mass(), entity2.body().charge()};
                    vec2 accel = inter->acceleration(body1, body2);
                    result[j + 2] += accel.x;
                    result[j + 3] += accel.y;
                }
            }
        }
        return result;
    }
}