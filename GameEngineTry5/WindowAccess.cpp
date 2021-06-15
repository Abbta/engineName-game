#include "WindowAccess.h"
#include "MainWindow.h"
namespace EngineName
{
	namespace Base
	{
		//when flags is changed, also changes flags in mainwindow
		unsigned int& WindowAccess::Flags::operator=(const unsigned int newFlags)
		{
			mp_windowFlags = newFlags;
			mpref_windowAccessRef.mpptr_mainWindowRef->get()->mp_windowFlags = newFlags;
			return mp_windowFlags;
		}

		//when title is changed, also changes title in mainwindow
		std::wstring& WindowAccess::Title::operator=(std::wstring newTitle)
		{
			mp_windowTitle = newTitle;
			mpref_windowAccessRef.mpptr_mainWindowRef->get()->mp_windowTitle = newTitle;
			return mp_windowTitle;
		}

		const int WindowAccess::CreationHeight::operator=(const int newHeight)
		{
			mp_height = newHeight;
			mp_windowAccesRef.mpptr_mainWindowRef->get()->mp_creationHeight = newHeight;
			return mp_height;
		}

		const int WindowAccess::CreationWidth::operator=(const int newWidth)
		{
			mp_width = newWidth;
			mp_windowAccesRef.mpptr_mainWindowRef->get()->mp_creationWidth = newWidth;
			return mp_width;
		}
	}
}
