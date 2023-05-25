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
        std::vector<sf::CircleShape> _blacks, _whites, _reds;
        Ox _ox;
        Oy _oy;
        sf::RectangleShape _backGround;
        mutable sf::CircleShape _grPoint;
        double _grX = 2, _grY = 300;
        int _targets=0;
        int _radius_reds=0;
        double _delta = 0;
        bool _isFormula = false;
        float _time;
    public:
        Field() = default;

        void generate();

        void setDelta(double newDelta);

        bool checkTarget();

        std::string getTargets();

        void setTargets(const int& targets);

        void setRadiusReds(const int& radius);

        void updateGraph();

        void setGrY(double newGrY);

        void changeFormulaStatus();

        bool checkCrash();

        double getGrX();
        double getGrY();

        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
        
        void updateTime(const float& time);
    };
}
