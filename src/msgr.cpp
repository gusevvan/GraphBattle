#include <SFML/Graphics.hpp>
#include <msgr.h>
#include <string>


using namespace msg;

Msg::Msg(std::string& str)
{
	m_font.loadFromFile("my_font.ttf");

	m_box.setSize(sf::Vector2f(600, 400));
	m_box.setFillColor(sf::Color(124, 124, 124));
	m_box.setPosition(100, 100);
	
	m_msg = str;

	m_text.setFont(m_font);
	m_text.setPosition(150, 150);
	m_text.setString(m_msg);
}

void Msg::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
	render.draw(m_box, states);
	render.draw(m_text, states);
}