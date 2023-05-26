#pragma once
#include <SFML/Graphics.hpp>

namespace ui
{
    class Button : public sf::Drawable
    {
    private:
        mutable sf::Font font;

        mutable sf::RectangleShape m_box;

        mutable sf::Text m_text;
    public:
        Button(char* newText);
        void draw(sf::RenderTarget& render, sf::RenderStates states) const;
        bool Contains(const int& x, const int& y);
        void setOutLine(const int& flag);
        void setTextColor(const int& r, const int& g, const int& b);
        void setPosition(const int& x, const int& y);
    };
}
