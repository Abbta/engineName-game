#include "TextRectangleConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a rectangle, put it and refs to it in correct storages
		TextRectangle& TextRectangleConstructor::build(const TextRectangle& textRectangle)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allTextRectangles.push_back(std::make_unique<TextRectangle>(textRectangle));
			this->mf_registerNewVisible(*mparr_allTextRectangles.back());
			return *this->mparr_allTextRectangles.back();
		}

		TextRectangle& TextRectangleConstructor::build(const Rectangle& rect, const std::wstring& text, const Drawing::Font& font, const Color& textColor)
		{
			return this->build(TextRectangle(rect, text, font, textColor));
		}
	}
}