#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <FormRec.h>
#include <string>
#include <sstream>
#include <time.h>
#include <textbox.h>

struct coord {
    double x;
    double y;
    coord(double xx, double yy) {
        x = xx;
        y = yy;
    }
};

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    tb::FocusController fc;
    tb::TextBox textBox;


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(1.f);
    sf::RectangleShape Ox(sf::Vector2f(800.f, 3.f));
    sf::RectangleShape Oy(sf::Vector2f(3.f, 800.f));
    sf::RectangleShape BackGround(sf::Vector2f(800.f, 600.f));
    BackGround.setFillColor(sf::Color::White);
    Oy.setPosition(400, 0);
    Ox.setPosition(0, 300);
    Oy.setFillColor(sf::Color::Yellow);
    Ox.setFillColor(sf::Color::Yellow);
    sf::CircleShape grPoint(3.f);
    grPoint.setFillColor(sf::Color::Blue);
    std::vector<coord> buffer;
    std::vector<std::vector<bool>> matrix;
    for (int i = 0; i <= 800; ++i) {
        std::vector<bool> cur(601, false);
        matrix.push_back(cur);
    }
    int rounds = rand() % 10 + 3;
    for (int k = 0; k < rounds; k++) {
        int Px = rand() % 800, Py = rand() % 600, radius = rand()%10000+1000;
        for (int i = 0; i <= 800; ++i) {
            for (int j = 0; j <= 600; ++j) {
                if ((i - Px) * (i - Px) + (j - Py) * (j - Py) <= radius) {
                    matrix[i][j] = true;
                }
            }
        }
    }
    shape.setFillColor(sf::Color::Black);
    bool flag1 = true, flag2 = false, flag3 = false;
    double x = 0, y = 0;
    std::string formula;
    buffer.emplace_back(400, 300);
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        window.draw(BackGround);
        window.draw(Ox);
        window.draw(Oy);
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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    flag3 = true;
                }
            }
        }

        if (flag2 == true && flag3) {
            auto a = textBox.getStr();
            for (int i = 0; i < textBox.getSize(); ++i) {
                formula += *(a + i);
            }
            x = 0;
            y = 0;
            buffer.emplace_back(400, 300);
            flag2 = false;
            flag1 = false;
        }

        for (int i = 0; i <= 800; ++i) {
            for (int j = 0; j <= 600; ++j) {
                if (matrix[i][j] == true) {
                    shape.setPosition(i, j);
                    window.draw(shape);
                }
            }
            if (flag1 == true) {
                flag2 = true;
            }
        }
        
        for (coord cur : buffer) {
            grPoint.setPosition(cur.x, cur.y);
            window.draw(grPoint);
        }
        if (!flag1) {
            for (int i = 0; i < 8; ++i) {
                x += 0.25;
                std::ostringstream strs;
                strs << x / 20;
                std::string value = strs.str();
                std::string term;
                for (int i = 0; i < formula.size(); ++i) {
                    if (formula[i] == 'x') {
                        term += value;
                    }
                    else {
                        term += formula[i];
                    }
                }
                y = 20 * fr::calculate(term);
                std::cout << x << " " << y << "\n";
                buffer.emplace_back(x + 400, -y + 300);
            }

            if (matrix[int(buffer.back().x)][int(buffer.back().y)] == true) {
                for (int i = 0; i <= 800; ++i) {
                    for (int j = 0; j <= 600; ++j) {
                        if ((i - buffer.back().x) * (i - buffer.back().x) + (j - buffer.back().y) * (j - buffer.back().y) <= 1000) {
                            matrix[i][j] = false;
                        }
                    }
                }
                buffer.clear();
                flag1 = true;
            }
        }
        window.display();
    }

    return 0;
}