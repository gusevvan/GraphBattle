#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <formula.h>
#include <string>
#include <sstream>
#include <textbox.h>
#include <field.h>

int main()
{

    tb::FocusController fc;
    tb::TextBox textBox;

    gm::Field field;

    gm::Formula formula;

    field.generate();
    

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    window.setFramerateLimit(60);

   

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        window.draw(field);
        window.draw(textBox);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (textBox.Contains(mousePos.x, mousePos.y))
                {
                    fc.setFocusObject(&textBox);
                }
                else
                {
                    fc.setFocusObject(0);
                }
            }
            tb::FocusObject* fo = fc.getFocusObject();
            if (fo != 0)
            {
                fo->event(event);
            }
            if (fc.getFocusObject()) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        fc.setFocusObject(0);
                    }
                }
            }
        }

        auto a = textBox.getStr();
        std::string text;
        for (int i = 0; i < textBox.getSize(); ++i) {
            text += *(a + i);
        }

        for (int i = 0; i < 8; ++i) {
            formula.setStr(text, field.getGrX());
            field.setGrY(20 * formula.calculate());
            field.updateGraph();
        }


        field.checkCrash();


        window.display();
    }

    return 0;
}