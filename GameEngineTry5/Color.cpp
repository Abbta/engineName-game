#include <iomanip>
#include <sstream>
#include "Color.h"
namespace EngineName
{
	namespace Object
	{
		//construct by string with format "RRGGBB" or "RRGGBBAA"
		Color::Color(const std::string& hex)
		{
			std::string colorString = hex;
			//account for user inputing hex markers
			if (colorString[0] == '#')
				//if the user uses # to mark hex
			{
				//remove first char
				colorString = colorString.substr(1);
			}
			if (colorString[1] == 'x')
				//if the user uses 0x to mark hex
			{
				//remove first two chars
				colorString = colorString.substr(2);
			}

			//check that it has RRGGBB or RRGGBBAA format
			if (colorString.length() < 6 || colorString.length() > 8 || colorString.length() % 2 == 1)
			{
				throw Exceptions::BasicException("invalid hex string when constructing color");
			}
			//red is the first two
			m_red = std::stoi(colorString.substr(0, 2), 0, 16);
			//green is 3:rd and 4:th
			m_green = std::stoi(colorString.substr(2, 2), 0, 16);
			//blue is 5:th and 6:th
			m_blue = std::stoi(colorString.substr(4, 2), 0, 16);
			//if we have two more chars then they are alpha
			if (colorString.length() > 6)
			{
				m_alpha = std::stoi(colorString.substr(6, 8), 0, 16);
			}
			else
			{
				m_alpha = 0xFF;
			}
		}

		//return color as a string with format "RRGGBBAA"
		Color::operator std::string() const
		{
			std::stringstream stream;
			stream << std::hex << m_red * 0x1000000 + m_green * 0x10000 + m_blue * 0x100 + m_alpha;
			return std::string(stream.str());
		}

		//return color as a winapi D2D1::ColorF class
		Color::operator D2D1::ColorF() const
		{
			return D2D1::ColorF(m_red / 255.0F, m_green / 255.0F, m_blue / 255.0F, m_alpha / 255.0F);
		}

		Color::operator D2D1_COLOR_F() const
		{
			return D2D1_COLOR_F{ m_red / 255.0F, m_green / 255.0F, m_blue / 255.0F, m_alpha / 255.0F};
		}
	}
}