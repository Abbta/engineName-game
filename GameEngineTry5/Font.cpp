#include "Font.h"
namespace EngineName
{
	namespace Drawing
	{
		Font& Font::operator=(const Font& b)
		{
			mp_fontName = b.mp_fontName;
			mp_fontSize = b.mp_fontSize;
			return *this;
		}
	}
}