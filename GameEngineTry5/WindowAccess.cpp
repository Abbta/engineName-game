#include "WindowAccess.h"
#include "MainWindow.h"
namespace EngineName
{
	namespace Base
	{
		//when flags is changed, also changes flags in mainwindow
		unsigned int& WindowAccess::WindowFlagsClass::operator=(const unsigned int newFlags)
		{
			mp_windowFlags = newFlags;
			mpref_windowAccessRef.mpptr_mainWindowRef->get()->mp_windowFlags;
			return mp_windowFlags;
		}

		//when title is changed, also changes title in mainwindow
		std::wstring& WindowAccess::WindowTitleClass::operator=(std::wstring newTitle)
		{
			mp_windowTitle = newTitle;
			mpref_windowAccessRef.mpptr_mainWindowRef->get()->mp_windowTitle;
			return mp_windowTitle;
		}
	}
}
