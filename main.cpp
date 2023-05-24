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

    std::vector<bt::Button*> buttons;

    bt::Button button("Fire");
    button.setPosition(350, 700);
    button.setTextColor(255, 102, 0);
    buttons.push_back(&button);

    bt::Button buttonEasy("Easy");
    buttonEasy.setPosition(10, 650);
    buttonEasy.setTextColor(0, 128, 0);
    buttons.push_back(&buttonEasy);

    bt::Button buttonNormal("Normal");
    buttonNormal.setPosition(10, 700);
    buttonNormal.setTextColor(255, 255, 0);
    buttons.push_back(&buttonNormal);

    bt::Button buttonHard("Hard");
    buttonHard.setPosition(10, 750);
    buttonHard.setTextColor(220, 20, 60);
    buttons.push_back(&buttonHard);



    gm::Field field;

    gm::Formula formula;


    

    sf::RenderWindow window(sf::VideoMode(800, 800), "GraphBattle");

    bool isFormula = false;

    //field.generate();
    bool hasStarted = false;

    int x = 0, y = 0;

    sf::Clock clock;


    while (window.isOpen())
    {
        sf::Event event;
        if (!isFormula) {
            window.clear();
        }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        field.updateTime(time);
        targets.setString(field.getTargets());
        window.draw(field);
        window.draw(uiPlace);
        window.draw(textBox);
        window.draw(button);
        for (int i = 1; i < buttons.size(); ++i)
        {
            window.draw(*buttons[i]);
        }
        window.draw(invate);
        window.draw(targets);

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (!isFormula) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                
                for (int i = 1; i < buttons.size(); ++i)
                {
                    buttons[i]->setOutLine((!hasStarted)*buttons[i]->Contains(mousePos.x, mousePos.y));
                }
                
                button.setOutLine((hasStarted) * button.Contains(mousePos.x, mousePos.y));
                textBox.setOutLine((hasStarted) * textBox.Contains(mousePos.x, mousePos.y));

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (hasStarted)
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
                    else
                    {
                        for (int i = 1; i < buttons.size(); ++i)
                        {
                            if (buttons[i]->Contains(mousePos.x, mousePos.y))
                            {

                                field.setTargets(i * 2 + 1);
                                field.setRadiusReds(40 - (i*10));
                                hasStarted = true;
                                field.generate();
                            }
                        }
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