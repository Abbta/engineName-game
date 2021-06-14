#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#include "Font.h"
#pragma once
namespace EngineName
{
	namespace Drawing
	{
		class TextFormatContainer
		{
		private:
			std::map <Font, CComPtr<IDWriteTextFormat>> mp_formats;
		public:
			CComPtr<IDWriteTextFormat>& getFont(CComPtr<IDWriteFactory>& writeFactory, const Font& font);
		};
	}
}

