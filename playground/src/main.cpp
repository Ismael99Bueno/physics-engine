#include <SFML/Graphics.hpp>

#include "prefab.hpp"
#include "interaction2D.hpp"
#include "engine2D.hpp"

using namespace physics;

#define WIDTH 1280.f
#define HEIGHT 720.f

class gravitation : public interaction2D
{
    vec2 acceleration(const body2D &b1, const body2D &b2) const override
    {
        return (b2.pos() - b1.pos()).normalized() * (b2.mass() / b1.pos().sq_dist(b2.pos()));
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    window.setView(sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(WIDTH, -HEIGHT)));

    engine2D eng(rk::rk4);
    entity2D &e1 = eng.add(), &e2 = eng.add();
    e1.body().pos({100.f, 0.f});
    e1.body().vel({0.f, -10.f});
    e1.dispatch();

    gravitation grav;
    grav.add(e1);
    grav.add(e2);
    eng.add(grav);

    const float r = 20.f;
    sf::CircleShape c1(r);
    c1.setFillColor(sf::Color::Green);
    c1.setOrigin(r, r);
    sf::CircleShape c2 = c1;
    c1.setPosition(100.f, 0.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(c1);
        window.draw(c2);
        window.display();
    }

    return 0;
}