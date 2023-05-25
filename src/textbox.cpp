#include "textbox.h"
using namespace tb;
TextBox::TextBox()
{
    m_newText = "";
    font.loadFromFile("my_font.ttf");

    carriage = 0;

    m_text.setPosition(240, 650);
    m_text.setString(m_newText.substring(0, 25));
    m_text.setFont(font);

    carriage_box.setSize(sf::Vector2f(1, 35));
    updateVCarriage();

    m_box.setFillColor(sf::Color::Blue);
    m_box.setSize(sf::Vector2f(370, 40));
    m_box.setPosition(240, 650);
    m_box.setOutlineColor(sf::Color::Cyan);
}
void TextBox::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
    render.draw(m_box, states);
    render.draw(m_text, states);
    render.draw(carriage_box, states);
}
void TextBox::setFocus()
{
    m_box.setFillColor(sf::Color::Red);
}
void TextBox::deleteFocus()
{
    m_box.setFillColor(sf::Color::Blue);
}
bool TextBox::Contains(const int& x, const int& y)
{
    return m_box.getGlobalBounds().contains(x, y);
}
void TextBox::event(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        char temp_char = event.text.unicode;
        //input
        switch (event.text.unicode)
        {
        case 0xD: //Return
            
            m_newText.insert(carriage, temp_char);
            carriage++;
            updateText();
            updateVCarriage();
            break;
        case 0x8://Backspace
            if (!m_newText.isEmpty())
            {
                if (carriage != 0)
                {
                    carriage--;
                }
                m_newText.erase(carriage);
                
                updateText();
                updateVCarriage();
                
                
            }
            break;
        default:
        {  
            m_newText.insert(carriage , static_cast<wchar_t>(event.text.unicode));
            carriage++;
            updateText();
            updateVCarriage();
        }
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            if (!m_newText.isEmpty())
            {
                if (carriage != 0)
                {
                    carriage--;
                    updateText();
                    updateVCarriage();
                }
            }
            break;
        case sf::Keyboard::Right:

            if (!m_newText.isEmpty())
            {
                if (carriage != (m_newText.getSize()))
                {
                    carriage++;
                    updateText();
                    updateVCarriage();
                }
            }
            break;
        default:
            break;
        }
    }
}
void TextBox::updateText()
{
    sf::String temp;
    if (carriage < 25)
    {
        temp = m_newText.substring(0, 25);
    }
    else
    {
        temp = m_newText.substring(carriage - 25, 25);
    }
    setText(temp);
}
void TextBox::updateVCarriage()
{
    carriage_box.setPosition((m_text.findCharacterPos(carriage)).x + 1, 655);
}

void TextBox::setOutLine(const int& flag)
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


const sf::Uint32* TextBox::getStr()
{
    return m_newText.getData();
}
int TextBox::getSize()
{
    return m_newText.getSize();
}

void TextBox::setText(const sf::String& str)
{
    m_text.setString(str);
}


FocusController::FocusController(FocusObject* obj) : m_object(obj)
{
    if (m_object != 0)
    {
        m_object->setFocus();
    }
}
void FocusController::setFocusObject(FocusObject* new_obj)
{
    if (m_object == new_obj)
        return;
    if (m_object != 0)
        m_object->deleteFocus();
    if (new_obj != 0)
        new_obj->setFocus();
    m_object = new_obj;
}
FocusObject* FocusController::getFocusObject()
{
    return m_object;
}