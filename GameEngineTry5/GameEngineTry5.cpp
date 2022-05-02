
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
* contains the winapi message loop although the actual loop is in MainWindow.cpp
* is outside of EngineName namespace so that the winapi can call it
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		std::unique_ptr<EngineName::Base::ObjectContainer> objectContainer{ std::make_unique<EngineName::Base::ObjectContainer>() };
		//creates world dynamically
		if (engineNameMain(*objectContainer) > 0)
			//here is where the dev creates all objects in world
			//returns the size of world as to only keep executing if objects are added
		{
			//stores the mainwindow in a variable
			EngineName::Base::MainWindow *ptrMainWindow{ &*objectContainer->mpptr_window };
			
			//creates the main window of app
			if (!ptrMainWindow->Create(
				ptrMainWindow->mp_windowTitle.c_str(),
				ptrMainWindow->mp_windowFlags,
				NULL,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				ptrMainWindow->mp_creationWidth,
				ptrMainWindow->mp_creationHeight
				))
				throw EngineName::Exceptions::BasicException("failed to create main window");

			//displays the window
			ShowWindow(ptrMainWindow->Window(), nCmdShow);

			//draws all visibles
			objectContainer->mpptr_window->mpptr_painter->mf_drawAll();


			//message loop, used by winapi to contain all runtime flow
			//every loop mainwindow.handlemessage will be called
			MSG msg = { };
			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
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