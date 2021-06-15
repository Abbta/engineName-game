#include "WidthAndHeight.h"
namespace EngineName
{
	namespace Base
	{
		Width::Width(MainWindow& mainWindow) :
			mp_mainWinRef(mainWindow)
		{
			mp_width = c_windowCreationDefaultWidth;
		}

		Width& Width::operator=(const unsigned int newWidth)
		{
			mp_width = newWidth;
			//recalculate
			return *this;
		}

		const FLOAT Width::toOutputWidth(const unsigned int width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(width / static_cast<double>(mp_width)) * (temp.right - temp.left);
		}

		const FLOAT Width::toOutputWidth(const signed int width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(width / static_cast<double>(mp_width)) * (temp.right - temp.left);
		}
		const FLOAT Width::toOutputWidth(const double width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(width / mp_width) * (temp.right - temp.left);
		}


		Height::Height(MainWindow& mainWindow)
			:mp_mainWinRef(mainWindow)
		{
			mp_height = c_windowCreationDefaultHeight;
		}

		Height& Height::operator=(const unsigned int newHeight)
		{
			mp_height = newHeight;
			//recalculate
			return *this;
		}

		const FLOAT Height::toOutputHeight(const unsigned int height) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(height / static_cast<double>(mp_height)) * (temp.bottom - temp.top);
		}

		const FLOAT Height::toOutputHeight(const signed int height) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(height / static_cast<double>(mp_height)) * (temp.bottom - temp.top);
		}
	}
}