#include "button.h"

using namespace bt;
Button::Button()
{
    font.loadFromFile("my_font.ttf");

    m_text.setPosition(230, 750);
    m_text.setFont(font);
    m_text.setColor(sf::Color(255, 102, 0));
    m_text.setString("Fire");

    m_box.setFillColor(sf::Color(190, 190, 190));
    m_box.setSize(sf::Vector2f(100, 40));
    m_box.setPosition(230, 750);
    m_box.setOutlineColor(sf::Color::Cyan);

}
void Button::draw(sf::RenderTarget& render, sf::RenderStates states)const
{
    render.draw(m_box, states);
    render.draw(m_text, states);
}
bool Button::Contains(const int& x, const int& y)
{
    return m_box.getGlobalBounds().contains(x, y);
}
void Button::event(const sf::Event& event, const int& x, const int& y)
{
    if (event.type == sf::Event::MouseMoved)
    {
        if (Contains(x, y))
        {
            this->m_box.setOutlineThickness(2);
        }
        else
        {
            this->m_box.setOutlineThickness(0);
        }
    }
}