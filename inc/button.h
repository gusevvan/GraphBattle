#pragma once
#include <SFML/Graphics.hpp>

namespace bt
{
    class Button : public sf::Drawable
    {
    private:
        mutable sf::Font font;

        mutable sf::RectangleShape m_box;

        mutable sf::Text m_text;
    public:
        Button();
        void draw(sf::RenderTarget& render, sf::RenderStates states) const;
        bool Contains(const int& x, const int& y);
        void setOutLine(const int& flag);
    };
}
