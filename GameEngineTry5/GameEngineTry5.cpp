/*
* Abbreviations:
*	eng: Engine, this program, the connection to winapi without anything added to world
*	dev: developer, the person using eng to develop their own windows application
* 	world: EngineName::Base::ObjectContainer world, an c++ object containing all things added by dev
*	app: application, the complete application containing winapi, eng and prog. The actual program that runs when you execute it
*   prog: program, the part of app created by dev
*/

#include "framework.h"
#include "GameEngineTry5.h"
#include "ObjectContainer.h"
#include "MainWindow.h"
#include "BaseIncludeLibraries.h"
#include <iostream>
#include "Visible.h" //test for debugging
int engineNameMain(EngineName::Base::ObjectContainer& world);

/*
* main function, the entry point of the application
* connects ENGINE NAME to the windows api
* creates world
* calls the main function of the engine with world as parameter
* creates the main window and shows it
* contains the winapi message loop although the actual loop happens in MainWindow.cpp
* should not have to be visible to dev
* is outside of EngineName namespace so that the winapi can call it
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		int a{ 5 + 3 };
		std::unique_ptr<EngineName::Base::ObjectContainer> objectContainer{ std::make_unique<EngineName::Base::ObjectContainer>() };
		//creates world as dynamically allocated memory, this is because world will contain all things in prog and will therefore be extremely memory demanding 
		if (engineNameMain(*objectContainer) > 0)
			//here is where the dev creates all objects in world
			//returns the size of world as to only do stuff if the dev does something
		{
			//stores the mainwindow in a variable
			EngineName::Base::MainWindow *ptrMainWindow{ &*objectContainer->mpptr_window };
			
			//creates the main window of app
			if (!ptrMainWindow->Create(ptrMainWindow->mp_windowTitle.c_str(), ptrMainWindow->mp_windowFlags))
				throw EngineName::Exceptions::BasicException("failed to create main window");

			//displays the window
			ShowWindow(ptrMainWindow->Window(), nCmdShow);


			//draw all visibles
			objectContainer->mpptr_window->mpptr_painter->mf_drawAll();

		//---------------
			MSG msg = { };
			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//message loop, used by winapi to contain all runtime flow
			//every loop mainwindow.handlemessage will be called
		}
	}
	catch (EngineName::Exceptions::BasicException& exception)
	{
		std::cout << "EngineName Basic exception: " << static_cast<std::string>(exception);
		return -1;
	}
	catch (std::exception& exception)
	{
		std::cout << "Standard library error: " << exception.what();
		return -1;
	}
	catch (...)
	{
		std::cout << "unknown error";
		return -1;
	}

	return 0;
}