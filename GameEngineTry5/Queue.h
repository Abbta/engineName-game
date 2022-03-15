#include "BaseIncludeLibraries.h"
#include "TaskContainer.h"
#pragma once
namespace EngineName
{
	namespace Action
	{
		class OnActionBase;
	}
	namespace Base
	{
		class ObjectContainer;
		struct ObjectContainerAccess;
		class MainWindow;
	}
	namespace Time
	{
		class Task;

		/*
		* Queue class
		* stores a ref to all task objects that has scheduled execution
		* also keeps track of what system time it was last time it was called
		*/
		class Queue
		{
		private:
			std::chrono::time_point<std::chrono::system_clock> mp_timeAtLastCall;
			TaskContainer mpc_taskContainer; //Just a bunch of std::list, should not need dynamic memory
			std::vector<Task*> mparr_theQueue;
			void mpf_addToQueue(Task& task);
			void mpf_update(Base::ObjectContainer& world);
		public:
			Queue() { mp_timeAtLastCall = std::chrono::system_clock::now(); }

			friend class Base::MainWindow;
			friend class Base::ObjectContainer;
			friend class Action::OnActionBase;
			friend struct Base::ObjectContainerAccess;
		};
	}
}