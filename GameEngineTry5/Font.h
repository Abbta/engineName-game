#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#include "Typedefs.h"
#pragma once
namespace EngineName
{
	namespace Drawing
	{
		/*
		* Font class
		* represents a font for text output
		* assigns a unique ID for all fonts to enable comparison
		*/
		class Font
		{
		private:
			std::wstring mp_fontName;
			unsigned short mp_fontSize;
			//some font parameters are not currently implemented to be changed
			const std::wstring mpcxr_lang = L"en-us";
			const CComPtr<IDWriteFontCollection> mpcxr_collection = nullptr;
			const unsigned short mpcxr_weight = DWRITE_FONT_WEIGHT_REGULAR; //the inside matters more than the outside, you don't need this
			const unsigned short mpcxr_style = DWRITE_FONT_STYLE_NORMAL;
			const unsigned short mpcxr_stretch = DWRITE_FONT_STRETCH_NORMAL;
		public:
			Font(const std::wstring& font = L"Arial", const unsigned short size = 11) {
				mp_fontName = font;
				mp_fontSize = size;
			}

			friend class TextFormatContainer;

			//returns an ID which is unique and constant for each font, note that it is not constant for a certain class
			operator td_ID() const
			{
				//needs to be overhauled if for example weight is implemented in eng
				//assumes there is no two font names with same name length and same middle character in name
				return (mp_fontSize + ((mp_fontName.length() * mp_fontName[mp_fontName.length() / 2]) << 0x10));
			}

			//compares by id, for sorting
			bool operator<(const Font& b) const
			{
				return static_cast<td_ID>(*this) < static_cast<td_ID>(b);
			}

			Font& operator=(const Font& b);
		};

	}
}