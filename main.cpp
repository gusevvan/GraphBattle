#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <formula.h>
#include <string>
#include <sstream>
#include <textbox.h>
#include <field.h>
#include <button.h>

int main()
{

    tb::FocusController fc;
    tb::TextBox textBox;


    sf::Font font;
    font.loadFromFile("my_font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("Enter formula here:");
    text.setColor(sf::Color::White);
    text.setPosition(80, 650);

    sf::RectangleShape uiPlace(sf::Vector2f(800.f, 200.f));
    uiPlace.setPosition(0.f, 600.f);
    uiPlace.setFillColor(sf::Color(124, 124, 124));

    bt::Button button;

    gm::Field field;

    gm::Formula formula;

    field.generate();
    

    sf::RenderWindow window(sf::VideoMode(800, 800), "GraphBattle");

    window.setFramerateLimit(60);

    bool isFormula = false;

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        window.draw(field);
        window.draw(uiPlace);
        window.draw(textBox);
        window.draw(button);
        window.draw(text);

        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            if (!isFormula) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                button.setOutLine(button.Contains(mousePos.x, mousePos.y));

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
                    if (button.Contains(mousePos.x, mousePos.y)) {
                        auto a = textBox.getStr();
                        std::string text;
                        for (int i = 0; i < textBox.getSize(); ++i) {
                            text += *(a + i);
                        }
                        button.setOutLine(0);
                        fc.setFocusObject(0);
                        formula.setStr(text);
                        isFormula = true;
                    }
                }
                tb::FocusObject* fo = fc.getFocusObject();
                if (fo != 0)
                {
                    fo->event(event);
                }
                if (fc.getFocusObject()) {
                    if (event.type == sf::Event::KeyPressed) {
                        auto a = textBox.getStr();
                        std::string text;
                        for (int i = 0; i < textBox.getSize(); ++i) {
                            text += *(a + i);
                        }
                        if (event.key.code == sf::Keyboard::Enter) {
                            fc.setFocusObject(0);
                            button.setOutLine(0);
                            formula.setStr(text);
                            isFormula = true;
                        }
                    }
                }
            }
        }

        if (isFormula) {
            for (int i = 0; i < 8; ++i) {
                field.setGrY(20 * formula.calculate(field.getGrX()));
                field.updateGraph();
            }
            isFormula = !field.checkCrash();
        }


        window.display();
    }

    return 0;
}