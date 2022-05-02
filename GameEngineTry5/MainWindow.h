#include "WindowBaseClass.h" //contains the template used
#include "Constants.h"
#include "Painter.h"

#pragma once
namespace EngineName
{
	namespace Action
	{
		class OnActionBase;
	}
	namespace Base
	{
		class WindowAccess;
		class ObjectContainer;
		struct ObjectContainerAccess;

		/*
		* mainwindow class
		* is responsible for mainwindow interaction with winapi
		* contains functions and variables necessary for creation of window
		* also contains handleMessage which is the main loop of the program
		* contains painter which is responsible for all graphic output
		*/
		class MainWindow :
			public WindowBaseClass<MainWindow>
		{
		private:
			//variables used only in creation of window
			int mp_windowFlags;
			std::wstring mp_windowTitle;
			int mp_creationWidth;
			int mp_creationHeight;

			std::unique_ptr<Drawing::Painter> mpptr_painter;
			ObjectContainer& mp_world;
		public:

			MainWindow(ObjectContainer& world): mp_world(world),
				mp_windowFlags(c_mainWindowStandardFlags), mp_windowTitle(c_mainWindowStandardTitle),
				mp_creationHeight(c_windowCreationDefaultHeight), mp_creationWidth(c_windowCreationDefaultWidth),
				mpptr_painter(std::make_unique<Drawing::Painter>(world))
			{ }
			//functions necessary for creation
			PCWSTR  ClassName() const { return L"Sample Window Class"; }
			LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

			friend class WindowAccess;
			friend struct ObjectContainerAccess;
			friend class ObjectContainer;
			friend int WINAPI::wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);
		};
	}
}