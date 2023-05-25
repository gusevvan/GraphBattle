#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace msg
{
	class Msg : public sf::Drawable
	{
		mutable sf::Font m_font;
		mutable sf::String m_msg;
		mutable sf::RectangleShape m_box;
		mutable sf::Text m_text;
	public:
		Msg(std::string& str);
		virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
		void setString(std::string& str);
	};

}