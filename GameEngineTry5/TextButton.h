#pragma once
#include "Button.h"
#include "TextRectangle.h"
namespace EngineName
{
	namespace Object
	{
		class TextButton
			: public Button, public TextRectangle
		{
		public:
			TextButton(Button& button, const std::wstring& text = L"Lorem ipsum",
				const Drawing::Font& font = Drawing::Font(), const Color& textColor = Color("000000"))
				:Button(button), TextRectangle(static_cast<Rectangle>(button), text, font, textColor)
			{
			
			};

			här, m func overloads?
		};
	}
}


