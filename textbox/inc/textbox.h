#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


namespace tb
{
    class FocusObject
    {
    public:
        virtual void setFocus() = 0;
        virtual void deleteFocus() = 0;
        virtual void event(const sf::Event&) = 0;
    };



    class TextBox : public sf::Drawable, public FocusObject /*, public sf::Transformable */
    {
    private:
        mutable sf::Font font;
        
        mutable sf::RectangleShape m_box;
        
        mutable sf::Text m_text;
        mutable sf::String m_newText;
        
        mutable int carriage;
        mutable sf::RectangleShape carriage_box;
        
        int l_bound;
        int r_bound;

        int v_carriage;
    public:
        TextBox()
        {
            m_newText = "Input func";
            std::cout << *m_newText.getData();
            m_newText.insert(1, 'k');
            font.loadFromFile("my_font.ttf");
            
            v_carriage = 0;
            carriage = -1;
            l_bound = 0;
            r_bound = 4;
            
            m_text.setPosition(400, 500);
            m_text.setString(m_newText.substring(l_bound,5));
            m_text.setFont(font);
            
            carriage_box.setSize(sf::Vector2f(1, 30));
            updateVCarriage();

            m_box.setFillColor(sf::Color::Blue);
            m_box.setSize(sf::Vector2f(200, 40));
            m_box.setPosition(400, 500);
            
        }
        virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const
        {
            render.draw(m_box, states);
            render.draw(m_text, states);
            render.draw(carriage_box, states);
        }
        void setFocus() override
        {
            m_box.setFillColor(sf::Color::Red);
        }
        void deleteFocus() override
        {
            m_box.setFillColor(sf::Color::Blue);
        }
        virtual void event(const sf::Event& event)
        {
            if (event.type == sf::Event::TextEntered)
            {
                std::cout << m_newText.getSize()<<std::endl;
                std::cout << carriage<<std::endl;
                //Обработка ввода
                switch (event.text.unicode)
                {
                case 0xD: //Return
                    std::cout << "q";
                    if (carriage != -1)
                    {
                        char temp_char = event.text.unicode;
                        std::cout << temp_char << std::endl;
                        m_newText.insert(carriage + 1, temp_char);
                        carriage++;
                        updateText();
                        if (v_carriage != 4)
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
                            updateText();
                            carriage--;
                            if (v_carriage != 0)
                            {
                                v_carriage--;
                            }
                            updateVCarriage();
                        }
                    }
                    
                    break;
                default:
                {
                    if (carriage != -1)
                    {
                        m_newText.insert(carriage+1, static_cast<wchar_t>(event.text.unicode));
                        carriage++;
                        updateText();
                        if (v_carriage != 4)
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
                            if (v_carriage == 0) updateText();
                            carriage--;
                            
                        }
                    }
                    break;
                case sf::Keyboard::Right:
                    if (!m_newText.isEmpty())
                    {
                        if (carriage != (m_newText.getSize() - 1))
                            carriage++;
                        if (v_carriage != 4 && v_carriage!=m_newText.getSize())
                        {
                            v_carriage++;
                            updateVCarriage();
                        }
                    }
                    if(v_carriage==4)updateText();
                    break;
                default:
                    break;
                }
            }
        }
        
        bool Contains(const int& x, const int& y)
        {
            return m_box.getGlobalBounds().contains(x, y);
        }
        private:
        void setText(const sf::String& str)
        {
            m_text.setString(str);
        }
        void updateText()
        {
            sf::String temp;
            if (carriage > r_bound)
            {
                if (m_newText.getSize() > 5)
                {
                    temp = m_newText.substring(carriage - 4, 5);
                    r_bound = carriage;
                    l_bound = carriage - 4;
                }
                else
                {
                    r_bound = carriage;
                    l_bound = 0;
                }
            }
            else if (carriage < l_bound)
            {
                if (m_newText.getSize() > 5)
                {
                    temp = m_newText.substring(carriage, 5);
                    r_bound = carriage + 4;
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
                    temp = m_newText.substring(l_bound, 5);
                }
            }
            setText(temp);
        }
        void updateVCarriage()
        {
            carriage_box.setPosition(400 + v_carriage * 16 + 2, 505);
        }
    };



    class FocusController
    {
    private:
        FocusObject* m_object;
    public:

        FocusController(FocusObject* obj = 0) : m_object(obj)
        {
            if (m_object != 0)
            {
                m_object->setFocus();
            }
        }
        void setFocusObject(FocusObject* new_obj)
        {
            if (m_object == new_obj)
                return;
            if (m_object != 0)
                m_object->deleteFocus();
            if (new_obj != 0)
                new_obj->setFocus();
            m_object = new_obj;
        }
        FocusObject* getFocusObject()
        {
            return m_object;
        }

    
    };

}



