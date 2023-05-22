#include "textbox.h"
using namespace tb;
TextBox::TextBox()
{
    m_newText = "x";
    font.loadFromFile("my_font.ttf");

    v_carriage = 0;
    carriage = -1;
    l_bound = 0;
    r_bound = 24;

    m_text.setPosition(100, 700);
    m_text.setString(m_newText.substring(l_bound, 25));
    m_text.setFont(font);

    carriage_box.setSize(sf::Vector2f(1, 35));
    updateVCarriage();

    m_box.setFillColor(sf::Color::Blue);
    m_box.setSize(sf::Vector2f(370, 40));
    m_box.setPosition(100, 700);
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
void TextBox::event(const sf::Event& event, const int& x, const int& y)
{
    if (event.type == sf::Event::TextEntered)
    {
        //Обработка ввода
        switch (event.text.unicode)
        {
        case 0xD: //Return
            if (carriage != -1)
            {
                char temp_char = event.text.unicode;
                m_newText.insert(carriage + 1, temp_char);
                carriage++;
                updateText();
                if (v_carriage != 25)
                {
                    v_carriage++;
                    updateVCarriage();
                }
            }
            else
            {
                char temp_char = event.text.unicode;
                m_newText.insert(0, temp_char);
                carriage++;
                v_carriage++;
                updateVCarriage();
                updateText();
            }
            break;
        case 0x8://Backspace
            if (!m_newText.isEmpty())
            {
                if (carriage != -1)
                {
                    m_newText.erase(carriage);
                    if (v_carriage == 0)
                    {
                        updateText();
                        if (r_bound - l_bound < 24)
                        {
                            v_carriage = carriage;
                            updateVCarriage();
                        }

                    }
                    else
                    {
                        updateText();
                        v_carriage--;
                        updateVCarriage();

                    }
                    updateText();
                    carriage--;
                }
            }

            break;
        default:
        {
            if (carriage != -1)
            {
                m_newText.insert(carriage + 1, static_cast<wchar_t>(event.text.unicode));
                carriage++;
                updateText();
                if (v_carriage != 25)
                {
                    v_carriage++;
                    updateVCarriage();
                }
            }
            else
            {
                m_newText.insert(0, static_cast<wchar_t>(event.text.unicode));
                carriage++;
                v_carriage++;
                updateVCarriage();
                updateText();
            }
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
                if (carriage != -1)
                {
                    if (v_carriage != 0)
                    {
                        v_carriage--;
                        updateVCarriage();
                    }
                    if (v_carriage == 0)
                    {
                        updateText();
                    }
                    carriage--;
                }
            }
            break;
        case sf::Keyboard::Right:

            if (!m_newText.isEmpty())
            {
                if (carriage != (m_newText.getSize() - 1))
                {
                    carriage++;
                    if (v_carriage != 25)
                    {
                        v_carriage++;
                        updateVCarriage();
                    }
                    else if (v_carriage == 25)
                    {
                        updateVCarriage();
                        updateText();
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
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
void TextBox::updateText()
{
    sf::String temp;
    if (carriage > r_bound)
    {
        if (m_newText.getSize() > 25)
        {
            temp = m_newText.substring(carriage - 24, 25);
            r_bound = carriage;
            l_bound = carriage - 24;
        }
        else
        {
            r_bound = carriage;
            l_bound = 0;
        }
    }
    else if (carriage < l_bound)
    {
        if (m_newText.getSize() > 25)
        {
            temp = m_newText.substring(carriage, 25);
            r_bound = carriage + 24;
            l_bound = carriage;
        }
        else
        {
            r_bound = carriage;
            l_bound = 0;
        }
    }
    else
    {
        if (!m_newText.isEmpty())
        {
            temp = m_newText.substring(l_bound, 25);
        }
    }
    setText(temp);
}
void TextBox::updateVCarriage()
{
    carriage_box.setPosition((m_text.findCharacterPos(v_carriage)).x + 1, 705);
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