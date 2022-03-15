#include "MainWindow.h"
#include "WindowAccess.h"
#include "RectangleConstructor.h"
#include "CircleConstructor.h"
#include "Painter.h"
#include "Queue.h"
#include "MainWindow.h"
#include "ObjectTasks.h"
#include "TextRectangleConstructor.h"
#include "Color.h"
#include "Painter.h"
#include "WidthAndHeight.h"
#include "OnActionBase.h"
#include "ActionListener.h"
#include "NullVisible.h"
#include "ObjectContainerAccess.h"
#pragma once
namespace EngineName
{
	namespace Object
	{
		class Visible;
	}
	namespace Time
	{
		//class Move;
	}
	namespace Base
	{
		/*
		* objectcontainer class
		* class for world
		* contains all things and functions for adding everything that dev can add
		* creates mainwindow and windowaccess objects on construction
		*/
		class ObjectContainer
		{
		private:
			//these should only be interacted with by winapi or other world objects or access classes
			std::unique_ptr<MainWindow> mpptr_window; //will probably be large and is therefore dynamically allocated

			std::vector<Object::Visible*> mparr_allVisibles;

			Time::Queue mpc_theQueue;
			Action::ActionListener mp_actionListener;
			class BackgroundColor
			{
			private:
				Object::Color mp_color;
				Drawing::Painter& mp_painterref;
			public:
				BackgroundColor(Drawing::Painter& painterRef);

				BackgroundColor& operator=(const Object::Color& color);
			};
		public:
			ObjectContainer();
			int size(); //returns the amount of user added objects

			//TODO:
				//store all Visibles on screen in an array
				//make base class for objects
				//add visible objects, squares circle
				//add threads

			//public functions
			void drawVisible(const Object::Visible& visible) const;
			
			template<class T>
			T& schedule(const T& task, const int ms = 0)
			{
				//assumes task is derived from class task
				//construct and store a new task
				T& taskRef = mpc_theQueue.mpc_taskContainer.mpf_add(task);

				//add time to it
				taskRef.addTimeLeftInQueue(std::chrono::milliseconds(ms));

				//add a ref to it in the queue
				mpc_theQueue.mpf_addToQueue(taskRef);
				return taskRef;
			}


			//constructor classes
			Object::RectangleConstructor		rectangle;     //is fairly simple and is not currently considered to need dynamic allocation
			Object::CircleConstructor			circle;		   //--||--
			Object::TextRectangleConstructor	textRectangle; //--||--

			//access classes
			WindowAccess window;					//is fairly simple
			BackgroundColor backgroundColor;
			Width width;
			Height height;

			//static members
			Object::NullVisible nullVisible;

			//winapi functions that can access private world objects
			friend int WINAPI::wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);

			//other classes that can access private world objects
			//friends regularly accessing visibles from world
			friend class EngineName::Drawing::Painter;
			friend class Object::ObjectConstructor;
			friend class Object::PaintingOrder;
			//friends working closely together with world
			friend class MainWindow;
			//friends who are accessor classes
			friend struct ObjectContainerAccess;

			//TEMPORARY:
			Object::Vector mtemporary_origin;
		};
	}
}

