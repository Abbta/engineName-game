#include "BaseIncludeLibraries.h"
#include "Color.h"

#pragma once
namespace EngineName
{
	namespace Base
	{
		constexpr int c_mainWindowStandardFlags(WS_OVERLAPPEDWINDOW); //default: WS_OVERLAPPEDWINDOW, flags used when creating main window if dev supplies none
		const std::wstring c_mainWindowStandardTitle(L"EngineName Main Window"); //default: L"EngineName Main Window", name of app if dev supplies none
		constexpr int c_windowCreationDefaultWidth(1000); //default: 1000, width of window when created in windowed mode
		constexpr int c_windowCreationDefaultHeight(600); //default: 600, height of window when created in windowed mode

		constexpr int c_maxIterationCount(999); //default: 999, when there is a risk of infinite looping, the iteration variable is checked to not surpass this value
	}

	namespace Object
	{
		const Color c_defaultBackgroundColor("FFFFFFFF"); //default: Object::Color("FFFFFFFF"), default background color of main window
	}
}