#pragma once
#include "MainWindow.h"
#include "WindowAccess.h"
#include "RectangleConstructor.h"
#include "CircleConstructor.h"
#include "Painter.h"
#include "Queue.h"
#include "MainWindow.h"
#include "ObjectTasks.h"
#include "TextRectangleConstructor.h"
#include "TextButtonConstructor.h"
#include "Color.h"
#include "Painter.h"
#include "WidthAndHeight.h"
#include "OnActionBase.h"
#include "ActionListener.h"
#include "NullVisible.h"
#include "ObjectContainerAccess.h"
#include "ButtonConstructor.h"
#include "ObjectGroupConstructor.h"
#include "SceneConstructor.h"
#include "CounterConstructor.h"
#include "DevDefinedTasks.h"
#include "ActionListener.h"
#include "DisplayConstructor.h"
#include "ActivatableTButtonConstructor.h"
namespace EngineName
{
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
			std::unique_ptr<MainWindow> mpptr_window;
			std::vector<Object::Visible*> mparr_allVisibles;
			Time::Queue mpc_theQueue;
			Action::ActionListener mp_actionListener;
			//background color class
				//a class local to objectcontainer
					//that represents the background color of all windows
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
			int size() const; //returns the amount of user added objects

			//public functions-----
			//draws a visible
			bool drawVisible(const Object::Visible& visible) const;
			
			//schedules a task
			template<class T>
			T& schedule(const T& task, const td_scheduleTime ms = 0)
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

			//sets a scene to be the one displayed
			void setActiveScene(Object::Scene& scene);


			//constructor classes, also contains all objects-----
			Object::RectangleConstructor		  rectangle;
			Object::CircleConstructor			  circle;
			Object::TextRectangleConstructor	  textRectangle;
			Object::ButtonConstructor			  button;
			Object::TextButtonConstructor		  textButton;
			Object::ActivatableTButtonConstructor activatableTextButton;
			Object::ObjectGroupConstructor		  objectGroup;
			Object::SceneConstructor			  scene;
			Object::CounterConstructor			  counter;
			Object::DisplayConstructor			  display;


			//access classes-----
			WindowAccess window;
			BackgroundColor backgroundColor;
			Width width;
			Height height;


			//static members------
			//a nullvisible that is stored, instead of having a nullvisible constructor since only one is needed
			Object::NullVisible nullVisible;


			//friends-----
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


			//TEMPORARY:--------
			Object::Vector mtemporary_origin;
		};
	}
}

