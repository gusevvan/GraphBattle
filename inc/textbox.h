#pragma once
#include <SFML/Graphics.hpp>


namespace tb
{
    class FocusObject
    {
    public:
        virtual void setFocus() = 0;
        virtual void deleteFocus() = 0;
        virtual void event(const sf::Event&, const int& x=0, const int& y=0) = 0;
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
        TextBox();
        void draw(sf::RenderTarget& render, sf::RenderStates states) const;
        void setFocus() override;
        void deleteFocus() override;
        void event(const sf::Event& event, const int& x = 0, const int& y = 0);
        bool Contains(const int& x, const int& y);
        auto getStr();
        int getSize();
        private:
        void setText(const sf::String& str);
        void updateText();
        void updateVCarriage();
    };



    class FocusController
    {
    private:
        FocusObject* m_object;
    public:

        FocusController(FocusObject* obj = 0);
        void setFocusObject(FocusObject* new_obj);
        FocusObject* getFocusObject();
    
    };

}