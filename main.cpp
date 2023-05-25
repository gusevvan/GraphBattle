#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <formula.h>
#include <string>
#include <sstream>
#include <textbox.h>
#include <field.h>
#include <button.h>
#include <logger.h>
#include <msgr.h>

int main()
{
    
    tb::FocusController fc;
    tb::TextBox textBox;
    utils::Log::SetLogFile();
    

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

    sf::Text error_text;
    error_text.setFont(font);
    error_text.setFillColor(sf::Color::Red);
    error_text.setString("Error: ");
    error_text.setPosition(240, 750);

    
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

    std::string msg = "Welcome to the GraphShooter! \n";
    msg += "To play choose the level \n";
    msg += "Easy: 3 targets and 3-5 blocks \n";
    msg += "Normal: 5 targets and 5-8 blocks \n";
    msg += "Easy: 7 targets and 8-11 blocks \n";
    msg += "Your goal to hit all the targets \n";
    msg += "in the least number of attempts  \n";
    msg += "and as quickly as possible \n";
    msg += "Good luck! \n";

    msg::Msg hellomsg(msg);

    

    gm::Field field;

    gm::Formula formula;

    sf::Text error;
    error.setFont(font);
    error.setFillColor(sf::Color::Red);
    error.setString(formula.getError());
    error.setPosition(350, 750);

    

    sf::RenderWindow window(sf::VideoMode(800, 800), "GraphBattle");

    bool isFormula = false;

    
    bool hasStarted = false;

    int attempts = 0;
    float player_time = 0;
    bool has_played = true;
    
    sf::Text text_attempts;
    text_attempts.setFont(font);
    text_attempts.setString(static_cast<char>(attempts));
    text_attempts.setPosition(700, 700);
    
    sf::Text text_player_time;
    text_player_time.setFont(font);
    text_player_time.setString("0");
    text_player_time.setPosition(700, 750);

    
    
    
    int x = 0, y = 0;

    sf::Clock clock;

    sf::Clock player_clock;
    while (window.isOpen())
    {
        //variables
        sf::Event event;
        std::string text;
        
        //Check for drawing
        if (hasStarted)
        {
            player_time = player_clock.getElapsedTime().asMilliseconds();
            player_time /= 1000;
        }
        std::cout << has_played;
        if (!isFormula && !has_played) {
            window.clear();
        }
        
        
        //time
        float time = clock.getElapsedTime().asMicroseconds();
        //player_time = clock.getElapsedTime().asMicroseconds() + prev_time;
        clock.restart();
        time /= 800;
        
        //func 
        field.updateTime(time);
        targets.setString(field.getTargets());
        text_attempts.setString(std::to_string(attempts));
        //logDebug() << field.getGrX() << " " << field.getGrY();//logger for debug version
        
        //draw
        window.draw(field);
        window.draw(uiPlace);
        window.draw(textBox);
        window.draw(button);
        window.draw(error_text);
        window.draw(error);
        for (int i = 1; i < buttons.size(); ++i)
        {
            window.draw(*buttons[i]);
        }
        window.draw(invate);
        window.draw(targets);
        window.draw(text_attempts);

        int b = player_time*100;
        std::cout << "player time " << player_time << std::endl;
        std::string temp;

        temp.insert(0,std::to_string(b % 10));
        b /= 10;

        temp.insert(0, std::to_string(b % 10));
        b /= 10;

        temp.insert(0, ".");
        while (b != 0)
        {
            temp.insert(0, std::to_string(b % 10));
            b /= 10;
        }
        std::cout << temp << std::endl;
        text_player_time.setString(temp);
        window.draw(text_player_time);

        //in game msg
        if (!hasStarted)
        {
            if (!has_played)
            {
                if (field.getTargets() == "1")
                {
                    window.draw(hellomsg);
                }
            }
        }

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
                        if (button.Contains(mousePos.x, mousePos.y)) 
                        {
                            auto a = textBox.getStr();
                            text.clear();
                            for (int i = 0; i < textBox.getSize(); ++i) 
                            {
                                text += *(a + i);
                            }
                            button.setOutLine(0);
                            fc.setFocusObject(0);
                            formula.setStr(text);
                            formula.refreshError();
                            isFormula = true;
                            field.changeFormulaStatus();
                            field.setDelta(formula.calculate(0));
                            ++attempts;
                        }
                    }
                    else
                    {
                        for (int i = 1; i < buttons.size(); ++i)
                        {
                            if (buttons[i]->Contains(mousePos.x, mousePos.y))
                            {

                                field.setTargets(i);
                                field.setRadiusReds(40 - (i*10));
                                field.setRounds(i);
                                hasStarted = true;
                                field.generate();
                                player_clock.restart();
                                has_played = false;
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
                        text.clear();
                        for (int i = 0; i < textBox.getSize(); ++i) {
                            text += *(a + i);
                        }
                        if (event.key.code == sf::Keyboard::Enter) {
                            fc.setFocusObject(0);
                            button.setOutLine(0);
                            formula.setStr(text);
                            formula.refreshError();
                            field.changeFormulaStatus();
                            field.setDelta(formula.calculate(0));
                            isFormula = true;
                            ++attempts;
                        }
                    }
                }
            }
        }

        if (isFormula) {
            field.setGrY(formula.calculate(field.getGrX() - 2));
            error.setString(formula.getError());
            logRelease() << formula.getError()<<text;//logger for release version
            //logError() << formula.getError() << text;//logger for checkinkg errors version
            isFormula = !field.checkCrash() && !field.checkTarget() && !formula.getError().size();
            if (!isFormula) {
                field.changeFormulaStatus();
            }
            field.updateGraph();
        }

        if (field.getTargets() == "0") 
        {
            
            hasStarted = false;
            if(!has_played)
            {
            msg = "Game over! \n";
            std::cout << std::to_string(player_time) << std::endl;
            msg += "Your time: " + std::to_string(player_time);
            msg += " \n";
            msg += "Your attempts: " + std::to_string(attempts);
            std::cout << msg;
            msg::Msg endgameMsg(msg);
            window.draw(endgameMsg);
            attempts = 0;
            player_time = 0;
            }
            has_played = true;
        }
        
        window.display();
    }

    return 0;
}