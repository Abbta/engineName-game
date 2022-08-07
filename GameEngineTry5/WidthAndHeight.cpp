#include "WidthAndHeight.h"
namespace EngineName
{
	namespace Base
	{
		Width::Width(MainWindow& mainWindow) :
			mp_mainWinRef(mainWindow)
		{
			//start with assigning width of the actual window as width, meaning all kinds of widths are the same
			mp_width = c_windowCreationDefaultWidth;
		}

		//change width
		//TODO: update other widths when this changes, implent this when more type of widths are implemented
		Width& Width::operator=(const td_width newWidth)
		{
			mp_width = newWidth;
			//recalculate
			return *this;
		}

		//transform to winapi width, double overload as this causes no additional casts
		const FLOAT Width::toOutputWidth(const double width) const
		{
			//get rect of window
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			//(myWidth / width of output) = how much of the output area that is to be occupied by this width
			//this times the pixel width of the window gets how many pixels myWidth represents
			return static_cast<FLOAT>(width / mp_width) * (temp.right - temp.left);
		}

		//transform from winapi width
		const td_width Width::fromInputWidth(const FLOAT inputWidth) const
		{
			//inverse of toOutputWidth()
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<td_width>((inputWidth / (static_cast<double>(temp.right) - static_cast<double>(temp.left))) * mp_width);
		}

		//same but for height

		Height::Height(MainWindow& mainWindow)
			:mp_mainWinRef(mainWindow)
		{
			mp_height = c_windowCreationDefaultHeight;
		}

		Height& Height::operator=(const td_height newHeight)
		{
			mp_height = newHeight;
			//recalculate
			return *this;
		}

		const FLOAT Height::toOutputHeight(const double height) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<FLOAT>(height / mp_height) * (temp.bottom - temp.top);
		}

		const unsigned int Height::fromInputHeight(const short inputHeight) const
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			return static_cast<unsigned int>((inputHeight / (static_cast<double>(temp.right) - static_cast<double>(temp.left))) * mp_height);
		}
	}
}