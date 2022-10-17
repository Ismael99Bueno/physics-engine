#include <SFML/Graphics.hpp>

#define WIDTH 1280.f
#define HEIGHT 720.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.setView(sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(WIDTH, -HEIGHT)));
    shape.setOrigin(100.f, 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}