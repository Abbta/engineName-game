#include "TextFormatContainer.h"
#include "Font.h"
namespace EngineName
{
	namespace Drawing
	{
		CComPtr<IDWriteTextFormat>& TextFormatContainer::getFont(CComPtr<IDWriteFactory>& writeFactory, const Font& font)
		{
			if(writeFactory == nullptr)
				throw Exceptions::BasicException("writef factory is nullptr");

			std::map<Font, CComPtr<IDWriteTextFormat>>::iterator formatPair = mp_formats.find(font);

			if (formatPair == mp_formats.end())
			{
				std::map<Font, CComPtr<IDWriteTextFormat>>::iterator newFormatPair = mp_formats.emplace(font, CComPtr<IDWriteTextFormat>(nullptr)).first;
			
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

				formatPair = newFormatPair;
			}

			return formatPair->second;
		}
	}
}