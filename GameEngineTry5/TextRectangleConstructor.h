#pragma once
#include "ObjectConstructor.h"
#include "TextRectangle.h"
namespace EngineName{
    namespace Object{
        class TextRectangleConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<TextRectangle>> mparr_allTextRectangles;
        public:
            TextRectangleConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            TextRectangle& build(const TextRectangle& textRectangle);
            TextRectangle& build(const Rectangle& rect, const std::wstring& text = L"Lorem ipsum", const Drawing::Font& font = Drawing::Font(), const Color& textColor = Color("000000"));
        };
    }
}

