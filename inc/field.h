#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <formula.h>

namespace gm {

    struct point {
        double x;
        double y;
        point(double newX, double newY) {
            x = newX;
            y = newY;
        }
    };

    class Axis : public sf::Drawable {
    protected:
        sf::RectangleShape _line;
        std::vector<sf::RectangleShape> _segments;
        std::vector<sf::Text> _values;
    public:
        Axis() = default;
        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const {
            render.draw(_line, states);
            for (sf::RectangleShape shape : _segments) {
                render.draw(shape, states);
            }
            sf::Font font;
            font.loadFromFile("my_font.ttf");
            for (sf::Text text : _values) {
                text.setFont(font);
                render.draw(text, states);
            }
        }
    };

    class Ox : public Axis {
    public:
        Ox() {
            _line.setSize(sf::Vector2f(800.f, 3.f));
            _line.setPosition(0, 300);
            _line.setFillColor(sf::Color(255, 102, 0));
            sf::RectangleShape segment(sf::Vector2f(3.f, 10.f));
            segment.setFillColor(sf::Color(255, 102, 0));
            segment.setPosition(2, 297);
            sf::Text text;
            text.setFillColor(sf::Color(255, 102, 0));
            text.setPosition(5, 303);
            text.setCharacterSize(16);
            for (int i = 0; i < 10; ++i) {
                text.setString(static_cast<char>(i + '0'));
                _segments.emplace_back(segment);
                _values.emplace_back(text);
                text.move(sf::Vector2f(80.f, 0));
                segment.move(sf::Vector2f(80.f, 0));
            }
        }
    };

    class Oy : public Axis {
    public:
        Oy() {
            _line.setSize(sf::Vector2f(3.f, 600.f));
            _line.setPosition(2, 0);
            _line.setFillColor(sf::Color(255, 102, 0));
            sf::RectangleShape segment(sf::Vector2f(10.f, 3.f));
            segment.setFillColor(sf::Color(255, 102, 0));
            segment.setPosition(0, 0);
            sf::Text text;
            text.setFillColor(sf::Color(255, 102, 0));
            text.setPosition(5, 3);
            text.setCharacterSize(16);
            text.setString("10");
            _values.emplace_back(text);
            std::string value;
            for (int i = 9; i >= -9; --i) {
                if (i < 0) {
                    value += '-';
                }
                value += char(abs(i) + '0');
                text.setString(value);
                text.move(sf::Vector2f(0.f, 30.f));
                _segments.emplace_back(segment);
                _values.emplace_back(text);
                segment.move(sf::Vector2f(0.f, 30.f));
                value.clear();
            }
            _segments.emplace_back(segment);
            text.setString("-10");
            text.move(sf::Vector2f(0.f, 30.f));
            segment.move(sf::Vector2f(0.f, 30.f));
            _segments.emplace_back(segment);
            _values.emplace_back(text);
        }
    };

    class Field : public sf::Drawable {
    private:
        std::vector<point> _buffer;
        std::vector<sf::CircleShape> _blacks, _whites, _reds;
        Ox _ox;
        Oy _oy;
        sf::RectangleShape _backGround;
        double _grX, _grY;
    public:
        Field() = default;

        void generate() {
            srand(time(NULL));

            _backGround.setSize(sf::Vector2f(800.f, 602.f));
            _backGround.setFillColor(sf::Color::White);
            _grX = 0;
            _grY = 0;

            int rounds = rand() % 10 + 3;

            for (int i = 0; i < rounds; ++i) {
                int radius = rand() % 100 + 10, Px = rand() % 801, Py = rand() % 601;
                sf::CircleShape shape(radius);
                shape.setOrigin(radius, radius);
                shape.setPosition(Px, Py);
                shape.setFillColor(sf::Color::Black);
                _blacks.push_back(shape);
            }

            int targets = 5;
            
            for (int i = 0; i < targets; ++i) {
                int radius = 10, Px = rand() % 601 + 200, Py = rand() % 601;
                sf::CircleShape shape1(radius);
                shape1.setOrigin(radius, radius);
                shape1.setPosition(Px, Py);
                shape1.setFillColor(sf::Color::Red);
                _reds.push_back(shape1);
                sf::CircleShape shape2(radius + 3);
                shape2.setOrigin(radius + 3, radius + 3);
                shape2.setPosition(Px, Py);
                _whites.push_back(shape2);
            }

            sf::CircleShape shape(100);
            shape.setOrigin(sf::Vector2f(100.f, 100.f));
            shape.setPosition(2.f, 300.f);
            _whites.push_back(shape);
        }

        void updateGraph() {       
            _buffer.emplace_back(_grX + 2, -_grY + 300);
            _grX += 0.1;
        }

        void setGrY(double newGrY) {
            _grY = 30 * newGrY;
        }

        bool checkCrash() {
            bool isCrashed = false;
            if (_buffer.back().x > 800 || _buffer.back().y > 600 || _buffer.back().y < 0 || _buffer.back().x < 0) {
                _grX = 0;
                _grY = 0;
                _buffer.clear();
                return true;
            }
            for (sf::CircleShape shape : _blacks) {

                if ((shape.getPosition().x - _buffer.back().x) * (shape.getPosition().x - _buffer.back().x) +
                    (shape.getPosition().y - _buffer.back().y) * (shape.getPosition().y - _buffer.back().y)
                    <= shape.getRadius() * shape.getRadius()) {
                    isCrashed = true;
                    break;
                }
            }
            if (isCrashed) {
                for (sf::CircleShape shape : _whites) {
                    if ((shape.getPosition().x - _buffer.back().x) * (shape.getPosition().x - _buffer.back().x) +
                        (shape.getPosition().y - _buffer.back().y) * (shape.getPosition().y - _buffer.back().y)
                        <= (shape.getRadius() - 1) * (shape.getRadius() - 1)) {
                        isCrashed = false;
                        break;
                    }
                }
                if (isCrashed) {
                    sf::CircleShape shape(10);
                    shape.setOrigin(5, 5);
                    shape.setPosition(_buffer.back().x, _buffer.back().y);
                    _whites.push_back(shape);
                    _grX = 0;
                    _grY = 0;
                    _buffer.clear();
                }
            }
            return isCrashed;
        }

        double getGrX() {
            return _grX;
        }

        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const
        {
            render.draw(_backGround, states);
            
            for (sf::CircleShape shape : _blacks) {
                render.draw(shape, states);
            }

            for (sf::CircleShape shape : _whites) {
                render.draw(shape, states);
            }

            for (sf::CircleShape shape : _reds) {
                render.draw(shape, states);
            }

            render.draw(_ox, states);
            render.draw(_oy, states);

            sf::CircleShape grPoint(2.f);
            grPoint.setFillColor(sf::Color::Blue);

            if (_buffer.size()) {
                grPoint.move(_buffer.back().x, _buffer.back().y);
                render.draw(grPoint, states);
            }

            /*for (point current : _buffer) {
                std::cout << current.x << " " << current.y << "\n";
                grPoint.setPosition(current.x, current.y);
                render.draw(grPoint, states);
            }*/
        }
    };
}
