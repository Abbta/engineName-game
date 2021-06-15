#include "MainWindow.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		class Width
		{
		private:
			unsigned int mp_width;
			MainWindow& mp_mainWinRef;
		public:
			Width(MainWindow& mainWindow);

			operator const unsigned int() const { return mp_width; }
			Width& operator=(const unsigned int newWidth);
			const FLOAT toOutputWidth(const unsigned int width) const;
			const FLOAT toOutputWidth(const signed int width) const;
			const FLOAT toOutputWidth(const double width) const;
		};

		class Height
		{
		private:
			unsigned int mp_height;
			MainWindow& mp_mainWinRef;
		public:
			Height(MainWindow& mainWindow);

			operator const unsigned int() const { return mp_height; }
			Height& operator=(const unsigned int newHeight);
			const FLOAT toOutputHeight(const unsigned int height) const;
			const FLOAT toOutputHeight(const signed int height) const;
		};
	}
}