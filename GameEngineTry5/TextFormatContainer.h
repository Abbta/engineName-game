#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#include "Font.h"
#pragma once
namespace EngineName
{
	namespace Drawing
	{
		/*
		* Text format container class
		* connects Font class to actual winapi fonts
		* same as how Brushcontainer connects Color class to a brushes
		*/
		class TextFormatContainer
		{
		private:
			//map containing all allocated fonts together with their associated Font classes
			std::map <Font, CComPtr<IDWriteTextFormat>> mp_formats;
		public:
			//gets a certain font, allocates it if it does not already exist
			CComPtr<IDWriteTextFormat>& getFont(CComPtr<IDWriteFactory>& writeFactory, const Font& font);
		};
	}
}

