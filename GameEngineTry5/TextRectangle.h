#pragma once
#pragma warning( disable : 4250) //the correct mpf_drawSelf is inherited via dominance
#include "Rectangle.h"
#include "Font.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * TextRectangle class
        * a rectangle with text inside of it
        * inherits rectangle virtually to 
        */
        class TextRectangle :
            virtual public Rectangle
        {
        private:
            //performs drawing of itself if within a drawing context
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        protected:
            //variables associated to the text
            std::wstring     mp_text;
            Drawing::Font    mp_font;
            Color            mp_textColor;
        public:
            TextRectangle(const Rectangle& rect, const std::wstring& text = L"Lorem ipsum",
                const Drawing::Font& font = Drawing::Font(), const Color& textColor = Color("000000"))
                :Rectangle(rect), mp_text(text), mp_font(font), mp_textColor(textColor) {};
        
            friend class ActivatableTButton;
        };
    }
}

