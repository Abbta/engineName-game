#pragma once
#include "Button.h"
#include "TextRectangle.h"
namespace EngineName
{
	namespace Object
	{
		/*
		* TextButton class
		* A button with a textrectangle instead of a normal rectangle
		*/
		class TextButton
			: public Button, public TextRectangle
		{
		public:
			//constructor with button and params for text
			TextButton(const Button& button, const std::wstring& text = L"Lorem ipsum",
				const Drawing::Font& font = Drawing::Font(), const Color& textColor = Color("000000"))
				:Rectangle(button), Button(button), TextRectangle(static_cast<Rectangle>(button), text, font, textColor)
			{
			};

			//constructor with a textrectangle and task
			template<class t_TaskType>
			TextButton(const TextRectangle& textRectangle, const t_TaskType& onClickTask)
				:Rectangle(textRectangle), TextRectangle(textRectangle), Button(textRectangle, onClickTask)
			{

			}
		};
	}
}


