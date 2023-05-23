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

    sf::Text invate;
    invate.setFont(font);
    invate.setString("y=");
    invate.setPosition(200, 650);
    sf::Text targets;
    targets.setFont(font);
    targets.setFillColor(sf::Color::Red);
    targets.setString("5");
    targets.setPosition(700, 650);

    sf::RectangleShape uiPlace(sf::Vector2f(800.f, 200.f));
    uiPlace.setPosition(0.f, 602.f);
    uiPlace.setFillColor(sf::Color(124, 124, 124));

    bt::Button button("Fire");
    button.setPosition(350, 700);
    button.setTextColor(255, 102, 0);

    gm::Field field;

    gm::Formula formula;

    field.generate();
    

    sf::RenderWindow window(sf::VideoMode(800, 800), "GraphBattle");

    bool isFormula = false;

    int x = 0, y = 0;

    while (window.isOpen())
    {
        sf::Event event;
        if (!isFormula) {
            window.clear();
        }
        targets.setString(field.getTargets());
        window.draw(field);
        window.draw(uiPlace);
        window.draw(textBox);
        window.draw(button);
        window.draw(invate);
        window.draw(targets);

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
                        field.changeFormulaStatus();
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
                            field.changeFormulaStatus();
                            isFormula = true;
                        }
                    }
                }
            }
        }

        if (isFormula) {
            field.setGrY(formula.calculate(field.getGrX()));
            isFormula = !field.checkCrash() && !field.checkTarget();
            if (!isFormula) {
                field.changeFormulaStatus();
            }
            field.updateGraph();
        }


        window.display();
    }

    return 0;
}