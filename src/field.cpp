#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <formula.h>
#include <field.h>

namespace gm {
    void Axis::draw(sf::RenderTarget& render, sf::RenderStates states) const {
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
    Ox::Ox() {
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

    Oy::Oy() {
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

    void Field::generate() {
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

        for (int i = 0; i < _targets; ++i) {
            int radius = 14, Px = rand() % 601 + 200, Py = rand() % 601;
            sf::CircleShape shape1(radius);
            shape1.setOrigin(radius, radius);
            shape1.setPosition(Px, Py);
            shape1.setFillColor(sf::Color::Red);
            shape1.setOutlineColor(sf::Color::White);
            shape1.setOutlineThickness(2);
            _reds.push_back(shape1);
            /*sf::CircleShape shape2(radius + 3);
            shape2.setOrigin(radius + 3, radius + 3);
            shape2.setPosition(Px, Py);
            _whites.push_back(shape2);*/
        }

        sf::CircleShape shape(100);
        shape.setOrigin(sf::Vector2f(100.f, 100.f));
        shape.setPosition(2.f, 300.f);
        _whites.push_back(shape);
    }

    void Field::hitTarget() {
        for (int i = 0; i < _reds.size(); ++i) {
            if ((_reds[i].getPosition().x - point_x) * (_reds[i].getPosition().x - point_x) +
                (_reds[i].getPosition().y - point_y) * (_reds[i].getPosition().y - point_y)
                <= _reds[i].getRadius() * _reds[i].getRadius()) { 
                    sf::CircleShape shape(14);
                    shape.setOrigin(14, 14);
                    shape.setPosition(_reds[i].getPosition().x, _reds[i].getPosition().y);
                    _whites.push_back(shape);
                    --_targets;
            }
        }
    }

    std::string Field::getTargets() {
        std::ostringstream strs;
        strs << _targets;
        return strs.str();

    }

    void Field::setTargets(int targets) {
        _targets = targets;
    }

    void Field::updateGraph() {
        point_x = _grX + 2;
        point_y = -_grY + 300;
        _grX += 0.1;
    }

    void Field::setGrY(double newGrY) {
        _grY = 30 * newGrY;
    }

    bool Field::checkCrash() {
        bool isCrashed = false;
        if (point_x > 800 || point_y > 600 || point_y < 0 || point_x < 0) {
            _grX = 0;
            _grY = 0;
            
            return true;
        }
        for (sf::CircleShape shape : _blacks) {

            if ((shape.getPosition().x - point_x) * (shape.getPosition().x - point_x) +
                (shape.getPosition().y - point_y) * (shape.getPosition().y - point_y)
                <= shape.getRadius() * shape.getRadius()) {
                isCrashed = true;
                break;
            }
        }
        if (isCrashed) {
            for (sf::CircleShape shape : _whites) {
                if ((shape.getPosition().x - point_x) * (shape.getPosition().x - point_x) +
                    (shape.getPosition().y - point_y) * (shape.getPosition().y - point_y)
                    <= (shape.getRadius() - 1) * (shape.getRadius() - 1)) {
                    isCrashed = false;
                    break;
                }
            }
            if (isCrashed) {
                sf::CircleShape shape(10);
                shape.setOrigin(5, 5);
                shape.setPosition(point_x, point_y);
                _whites.push_back(shape);
                _grX = 0;
                _grY = 0;
                
            }
        }
        return isCrashed;
    }

    void Field::changeFormulaStatus() {
        _isFormula = !_isFormula;
    }
    void Field::draw(sf::RenderTarget& render, sf::RenderStates states) const
    {
        if (!_isFormula) {
            render.draw(_backGround, states);

            for (sf::CircleShape shape: _blacks) {
                render.draw(shape, states);
            }

            for (sf::CircleShape shape: _reds) {
                render.draw(shape, states);
            }

            for (sf::CircleShape shape : _whites) {
                render.draw(shape, states);
            }

            render.draw(_ox, states);
            render.draw(_oy, states);
        }
        sf::CircleShape grPoint(2.f);
        grPoint.setFillColor(sf::Color::Blue);

        grPoint.setPosition(point_x, point_y);
        render.draw(grPoint, states);

        /*for (point current : _buffer) {
            std::cout << current.x << " " << current.y << "\n";
            grPoint.setPosition(current.x, current.y);
            render.draw(grPoint, states);
        }*/
    }
}