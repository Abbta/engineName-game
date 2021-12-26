#pragma once
#include "Rectangle.h"
#include "Font.h"
namespace EngineName
{
    namespace Object
    {
        class TextRectangle :
            virtual public Rectangle
        {
        private:
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        protected:
            std::wstring     mp_text;
            Drawing::Font    mp_font;
            Color            mp_textColor;
        public:
            TextRectangle(const Rectangle& rect, const std::wstring& text = L"Lorem ipsum",
                const Drawing::Font& font = Drawing::Font(), const Color& textColor = Color("000000"))
                :Rectangle(rect), mp_text(text), mp_font(font), mp_textColor(textColor) {};
        
        };
    }
}

