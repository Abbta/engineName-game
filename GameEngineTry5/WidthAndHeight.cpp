#include "WidthAndHeight.h"
namespace EngineName
{
	namespace Base
	{
		Width::Width(MainWindow& mainWindow) :
			mp_mainWinRef(mainWindow)
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			mp_width = temp.right - temp.left;
		}

		Width& Width::operator=(const unsigned int newWidth)
		{
			mp_width = newWidth;
			//recalculate
		}

		const FLOAT Width::toOutputWidth(const unsigned int width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return (width / static_cast<double>(mp_width)) * (temp.right - temp.left);
		}

		const FLOAT Width::toOutputWidth(const signed int width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return (width / static_cast<double>(mp_width)) * (temp.right - temp.left);
		}
		const FLOAT Width::toOutputWidth(const double width) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return (width / mp_width) * (temp.right - temp.left);
		}


		Height::Height(MainWindow& mainWindow)
			:mp_mainWinRef(mainWindow)
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			mp_height = temp.bottom - temp.top;
		}

		Height& Height::operator=(const unsigned int newHeight)
		{
			mp_height = newHeight;
			//recalculate
		}

		const FLOAT Height::toOutputHeight(const unsigned int height) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return (height / static_cast<double>(mp_height)) * (temp.bottom - temp.top);
		}

		const FLOAT Height::toOutputHeight(const signed int height) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return (height / static_cast<double>(mp_height)) * (temp.bottom - temp.top);
		}
	}
}