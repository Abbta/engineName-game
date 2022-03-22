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
		class Task;
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
		class VisibleGroup;
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
			static Time::TaskContainer&				 getTaskContainer(ObjectContainer& world);
			static Time::Queue&						 getQueue(ObjectContainer& world);
			static Action::ActionListener&			 getActionListener(ObjectContainer& world);
			static WindowAccess&					 getWindowAccessor(ObjectContainer& world);
			//static ObjectContainer::BackgroundColor& getBackgroundColor(ObjectContainer& world);
			//man fuck backgroundColor, all my homies hate classes defined in other classes
			static Width&							 getWidth(ObjectContainer& world);
			static Height&							 getHeight(ObjectContainer& world);
			static Object::CounterConstructor&		 getCounter(ObjectContainer& world);
			static const Object::VisibleGroup*   	 getActiveScene(ObjectContainer& world);

			//Functions
			static void								 drawVisible(ObjectContainer& world, const Object::Visible& visible);
			template<class T>
			static T& schedule(ObjectContainer& world, const T& task, const int ms = 0)
			{
				//try catch in order to properly delete task in case of error
				T* taskMemoryPtr = new T(task);
				try
				{
					mpf_scheduleImpl(world, taskMemoryPtr, ms);
					return *taskMemoryPtr;
				}
				//TODO: add specific catch
				catch (...)
				{
					delete taskMemoryPtr;
					throw Exceptions::BasicException("scheduling of task aborted\n");
				}
			}

		private:
			static Time::Task* mpf_scheduleImpl(ObjectContainer& world, Time::Task* dynamicallyAllocatedTask, const int ms = 0);
		};
	}
}

