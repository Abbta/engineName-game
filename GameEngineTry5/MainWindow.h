#include "WindowBaseClass.h" //contains the template used
#include "Constants.h"
#include "Painter.h"

#pragma once
namespace EngineName
{
	namespace Base
	{
		class WindowAccess; //forward declaration for friend statement
		class ObjectContainer;

		/*
		* mainwindow class
		* derives from windowbaseclass
		* is responsible for mainwindow interaction with winapi
		* contains functions and variables necessary for creation of window
		* also contains handleMessage which is the main loop of the program
		* this class should not be directly accesed by dev
		*/
		class MainWindow :
			public WindowBaseClass<MainWindow>
		{
		private:
			int mp_windowFlags; //only used in creation of window
			std::wstring mp_windowTitle; //only used in creation of window
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

			//private functions are only to be accesed by eng
			friend class WindowAccess;
			friend class ObjectContainer;
			friend class Object::TextRectangle; //used for accessing painter to draw text
			friend int WINAPI::wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);
		};
	}
}