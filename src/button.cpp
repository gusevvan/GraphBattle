#include "button.h"

using namespace bt;
Button::Button(char* newText)
{
    font.loadFromFile("my_font.ttf");

    
    m_text.setFont(font);
    m_text.setString(newText);

    m_box.setFillColor(sf::Color(190, 190, 190));
    m_box.setSize(sf::Vector2f(100, 40));
    m_box.setOutlineColor(sf::Color::Cyan);

}
void Button::draw(sf::RenderTarget& render, sf::RenderStates states)const
{
    render.draw(m_box, states);
    render.draw(m_text, states);
}
void Button::setPosition(const int& x, const int& y)
{
    m_box.setPosition(x, y);
    m_text.setPosition(x, y);
}
void Button::setTextColor(const int& r, const int& g, const int& b)
{
    m_text.setColor(sf::Color(r, g, b));
}
bool Button::Contains(const int& x, const int& y)
{
    return m_box.getGlobalBounds().contains(x, y);
}
void Button::setOutLine(const int& flag)
{
    if (flag == 1)
    {
        this->m_box.setOutlineThickness(2);
    }
    else
    {
        this->m_box.setOutlineThickness(0);
    }
}