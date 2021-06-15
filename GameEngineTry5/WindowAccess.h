#include "BasicVariableException.h"
#include "Constants.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		class MainWindow; //forward declaration for referencing in variables

		/*
		* windowaccess class
		* a class used for giving dev access to some functions and variables in mainwindow under certain circumstances
		* ensures safe interaction with winapi elements
		* contains classes with the sole purpose of holding a mock variable that does necessary operations to the original when accesed
		*/
		class WindowAccess
		{
		private:

			/*
			* windowflagsclass class
			* small container class holding what flags to use in window creation
			* when the variable is changed it will also change the corresponding variable in mainwindow
			*/
			class Flags
			{
			private:
				//OPTIONAL TODO:
					//add custom flags that this class then translates to winapi flags
				unsigned int mp_windowFlags;
				WindowAccess& mpref_windowAccessRef; //instead of holding ref to mainwindow it holds ref to windowacces wiich in turn has a ref to mainwindow
			public:
				Flags(WindowAccess &windowAccessRef) : 
					mp_windowFlags(c_mainWindowStandardFlags), mpref_windowAccessRef(windowAccessRef) {}
				unsigned int& operator=(const unsigned int newFlags);
				//OPTIONAL TODO:
					//add more operators for more cases (+=, &, |)
			};

			/*
			* windowtitleclass class
			* small container class holding the title of the window
			* when the variable is changed it will also change the corresponding variable in mainwindow
			*/
			class Title
			{
			private:
				std::wstring mp_windowTitle;
				WindowAccess& mpref_windowAccessRef; //instead of holding ref to mainwindow it holds ref to windowacces wiich in turn has a ref to mainwindow
			public:
				Title(WindowAccess& windowAccessRef) : 
					mp_windowTitle(c_mainWindowStandardTitle), mpref_windowAccessRef(windowAccessRef) {}
				std::wstring& operator=(std::wstring newTitle);
			};

			class CreationWidth
			{
			private:
				int mp_width;
				WindowAccess& mp_windowAccesRef;
			public:
				CreationWidth(WindowAccess& windowAccessRef)
					: mp_width(c_windowCreationDefaultWidth), mp_windowAccesRef(windowAccessRef) {}
				const int operator=(const int newWidth);
			};

			class CreationHeight
			{
			private:
				int mp_height;
				WindowAccess& mp_windowAccesRef;
			public:
				CreationHeight(WindowAccess& windowAccessRef)
					: mp_height(c_windowCreationDefaultWidth), mp_windowAccesRef(windowAccessRef) {}
				const int operator=(const int newHeight);
			};

			std::unique_ptr<MainWindow>* mpptr_mainWindowRef;
		public:
			WindowAccess(std::unique_ptr<MainWindow, std::default_delete<MainWindow>>* mainWindowRef): mpptr_mainWindowRef(mainWindowRef), flags(*this), title(*this) {}
			//container classes
			Flags flags;
			Title title;
			CreationHeight creationHeight;
			CreationWidth creationWidth;
		};
	}
}
