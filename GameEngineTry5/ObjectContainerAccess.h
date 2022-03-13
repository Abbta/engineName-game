//#include as sparsely as possible here
#pragma once
#include "BaseIncludeLibraries.h"
namespace EngineName
{
	namespace Drawing
	{
		class Painter;
	}
	namespace Time
	{
		class Queue;
		class TaskContainer;
	}
	namespace Action
	{
		class ActionListener;
	}
	namespace Object
	{
		class CounterConstructor;
		class Visible;
	}
	namespace Base
	{
		class ObjectContainer;
		class WindowAccess;
		class Width;
		class Height;

		/*
		* ObjectContainerAccess
		* struct
		* Used for accessing objects within ObjectContainer
		* Stores no classes itself in order to not require any #includes
			for a safer #include of this file compared to that of ObjectContainer.
			Issues related to this most often occur with the use of template classes.
		* Also reduces the amount of needed friends for ObjectContainer 
		*/
		struct ObjectContainerAccess
		{
			//world is allowed to be store here as a ref or ptr but
				//for this version it was decided that functions 
				//wanting to access world must also show that they
				//have a world ref themselves. Also this means that the struct
				//can be static.

			//Getteres
			static Drawing::Painter&				 getPainter(ObjectContainer& world);
			static Time::Queue&						 getQueue(ObjectContainer& world);
			static Time::TaskContainer&				 getTaskContainer(ObjectContainer& world);
			static Action::ActionListener&			 getActionListener(ObjectContainer& world);
			static WindowAccess&					 getWindowAccessor(ObjectContainer& world);
			//static ObjectContainer::BackgroundColor& getBackgroundColor(ObjectContainer& world);
			//man fuck backgroundColor, all my homies hate classes defined in other classes
			static Width&							 getWidth(ObjectContainer& world);
			static Height&							 getHeight(ObjectContainer& world);
			static Object::CounterConstructor&		 getCounter(ObjectContainer& world);
			static void								 drawVisible(ObjectContainer& world, const Object::Visible& visible);

			//functions
			template<class T>
			static T& schedule(ObjectContainer& world, const T& task, const int ms = 0)
			{
				//assumes task is derived from class task
				//construct and store a new task
				T& taskRef = getTaskContainer(world).mpf_add(task);

				//add time to it
				taskRef.addTimeLeftInQueue(std::chrono::milliseconds(ms));

				//add a ref to it in the queue
				getQueue(world).mpf_addToQueue(taskRef);
				return taskRef;
			}

		private:
			const void* mpf_scheduleBypassingTemplate(ObjectContainer& world, const void*, )
		};
	}
}

