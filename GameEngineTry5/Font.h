#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#pragma once
namespace EngineName
{
	namespace Drawing
	{
		class Font
		{
		private:
			std::wstring mp_fontName;
			unsigned short mp_fontSize;
			const std::wstring mpcxr_lang = L"en-us";
			const CComPtr<const IDWriteFontCollection> mpcxr_collection = nullptr;
			const unsigned short mpcxr_weight = DWRITE_FONT_WEIGHT_REGULAR;
			const unsigned short mpcxr_style = DWRITE_FONT_STYLE_NORMAL;
			const unsigned short mpcxr_stretch = DWRITE_FONT_STRETCH_NORMAL;
		public:
			Font(const std::wstring& font = L"Arial", const unsigned short size = 11) {
				mp_fontName = font;
				mp_fontSize = size;
			}
			friend class TextFormatContainer;
			operator UINT64() const //an ID for the font
			{
				//needs to be overhauled if for example weight is implemented in eng
				//assumes there is no two font names with same name length and same middle character in name
				return (mp_fontSize + ((mp_fontName.length() * mp_fontName[mp_fontName.length() / 2]) << 0x10));
			}
			bool operator<(const Font& b) const
			{
				return static_cast<UINT64>(*this) < static_cast<UINT64>(b);
			}

			Font& operator=(const Font& b);
		};

	}
}