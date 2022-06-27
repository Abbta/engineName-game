#include "TextFormatContainer.h"
#include "Font.h"
namespace EngineName
{
	namespace Drawing
	{
		/*
		* get font member function
		* takes writefactory and a Font class as param
		* returns winapi font associated with Font
		*	either from already allocated inside map or allocates a new one and stores in map
		*/
		CComPtr<IDWriteTextFormat>& TextFormatContainer::getFont(CComPtr<IDWriteFactory>& writeFactory, const Font& font)
		{
			if(writeFactory == nullptr)
				throw Exceptions::BasicException("writef factory is nullptr");

			//get font from map
			std::map<Font, CComPtr<IDWriteTextFormat>>::iterator formatPair = mp_formats.find(font);

			//if font is not a part of map
			if (formatPair == mp_formats.end())
			{
				//add "empty" font to map
				std::map<Font, CComPtr<IDWriteTextFormat>>::iterator newFormatPair = mp_formats.emplace(font, CComPtr<IDWriteTextFormat>(nullptr)).first;
			
				//create a winapi font at that place
				if(FAILED(writeFactory->CreateTextFormat(
					font.mp_fontName.c_str(),
					font.mpcxr_collection,
					DWRITE_FONT_WEIGHT(font.mpcxr_weight),
					DWRITE_FONT_STYLE(font.mpcxr_style),
					DWRITE_FONT_STRETCH(font.mpcxr_stretch),
					font.mp_fontSize,
					font.mpcxr_lang.c_str(),
					&(newFormatPair->second)
				)))
					throw Exceptions::BasicException("Failed creating textFormat");

				//get the newly created font
				formatPair = newFormatPair;
			}

			//return font
			return formatPair->second;
		}
	}
}