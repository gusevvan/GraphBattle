#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "GraphBattle");
    sf::RectangleShape Ox(sf::Vector2f(500.f,3.f)), Oy(sf::Vector2f(3.f, 500.f));
    sf::CircleShape shape(1.f);
    shape.setFillColor(sf::Color::Green);
    Ox.setPosition(0, 250);
    Oy.setPosition(250, 0);
    double x = 0, y = 0;
    window.draw(Ox);
    window.draw(Oy);
    std::string formula;
    std::getline(std::cin, formula);
    std::cout << "1";
    std::cout.flush();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        std::string part;
        for (int i = 0; i <= formula.size(); ++i) {
            if (i == formula.size() || formula[i] == ' ') {
                if (part == "cosx") {
                    y = 50 * cos(x / 50);
                }
            } else {
                part += formula[i];
            }
        }
        shape.setPosition(x + 250, -y + 250);
        window.draw(shape);
        x += 0.5;
        window.display();
        for (int i = 0; i < 1e7; ++i) {

        }
    }
}
