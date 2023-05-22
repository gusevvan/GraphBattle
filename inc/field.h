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

    class Field : public sf::Drawable {
    private:
        std::vector<point> _buffer;
        std::vector<sf::CircleShape> _blacks, _whites;
        sf::RectangleShape _Ox;
        sf::RectangleShape _Oy;
        sf::RectangleShape _backGround;
        double _grX, _grY;
    public:
        Field() = default;

        void generate() {
            srand(time(NULL));

            _backGround.setSize(sf::Vector2f(800.f, 600.f));
            _backGround.setFillColor(sf::Color::White);
            _Oy.setSize(sf::Vector2f(800.f, 3.f));
            _Oy.setPosition(0, 300);
            _Ox.setSize(sf::Vector2f(3.f, 600.f));
            _Ox.setPosition(400, 0);
            _Oy.setFillColor(sf::Color(255, 102, 0));
            _Ox.setFillColor(sf::Color(255, 102, 0));
            _buffer.emplace_back(400, 300);
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
        }

        void updateGraph() {       
            _buffer.emplace_back(_grX + 400, -_grY + 300);
            _grX += 0.25;
        }

        void setGrY(double newGrY) {
            _grY = newGrY;
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
                        <= 81) {
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

            render.draw(_Ox, states);
            render.draw(_Oy, states);

            for (point current : _buffer) {
                std::cout << current.x << " " << current.y << "\n";
                sf::CircleShape shape(3.f);
                shape.setFillColor(sf::Color::Blue);
                shape.setPosition(current.x, current.y);
                render.draw(shape, states);
            }
        }
    };
}
