#include <d2d1.h>
#include "BaseIncludeLibraries.h"
#pragma once
namespace EngineName
{
	namespace Object
	{
		/*
		* color class
		* class for storing colour of an object
		* instead of using winapi native ColorF class
		* stores colour privately
		* is accesed by type conversions
		*/
		class Color
		{
		private:
			unsigned char m_red;
			unsigned char m_blue;
			unsigned char m_green;
			unsigned char m_alpha;
		public:
			Color(const std::string& hex);
			Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 0): m_red(r), m_green(g), m_blue(b), m_alpha(a) {}

			//operators
			operator std::string() const;
			operator D2D1::ColorF() const;
			operator D2D1_COLOR_F() const;
		};
	}
}