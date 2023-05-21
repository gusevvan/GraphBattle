#include <SFML/Graphics.hpp>
#include "b/textbox.h"
#include <iostream>

using namespace tb;
int main()
{
    FocusController fc;
    sf::RenderWindow window(sf::VideoMode(800, 600), L"SFML window");  
    
    bool x = false;
    TextBox tb;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (tb.Contains(mousePos.x, mousePos.y))
                {
                    fc.setFocusObject(&tb);
                }
                else
                {
                    fc.setFocusObject(0);
                }
            }
            FocusObject* fo = fc.getFocusObject();
            if (fo != 0)
            {
                fo->event(event);
            }
        }
        window.clear();
        window.draw(tb);
        window.display();
    }

}