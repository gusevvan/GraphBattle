#pragma once
#include <iostream>
#include <sstream>
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
        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
    };

    class Ox : public Axis {
    public:
        Ox();
    };

    class Oy : public Axis {
    public:
        Oy();
    };

    class Field : public sf::Drawable {
    private:
        double point_x = 2;
        double point_y = 300;
        std::vector<sf::CircleShape> _blacks, _whites, _reds;
        Ox _ox;
        Oy _oy;
        sf::RectangleShape _backGround;
        double _grX, _grY;
        int _targets = 5;
        bool _isFormula = false;
    public:
        Field() = default;

        void generate();

        void hitTarget();

        std::string getTargets();

        void setTargets(int targets);

        void updateGraph();

        void setGrY(double newGrY);

        void changeFormulaStatus();

        bool checkCrash();
        double getGrX() {
            return _grX;
        }

        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
    };
}
