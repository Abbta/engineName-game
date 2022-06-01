#pragma once
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
	namespace Object
	{
		template<class t_CountType, class t_TaskType> class CounterImpl;
	}
	namespace Time
	{
		/*
		* Queue class
		* handles execution of tasks that has been scheduled
		* stores a ref to all task objects that has scheduled execution
		* also keeps track of what system time it was last time it was called
		*/
		class Queue
		{
		private:
			std::chrono::time_point<std::chrono::system_clock> mp_timeAtLastCall;
			//task container stores all tasks
			TaskContainer mpc_taskContainer;
			//vector containing ptrs to all tasks that are scheduled for execution at some time, sorted with least time left at back
			std::vector<Task*> mparr_theQueue;

			void mpf_addToQueue(Task& task);
			void mpf_update(Base::ObjectContainer& world);
		public:
			Queue() { mp_timeAtLastCall = std::chrono::system_clock::now(); }

			friend class Base::MainWindow;
			friend class Base::ObjectContainer;
			friend class Action::OnActionBase;
			template<class t_CountType, class t_TaskType> friend class Object::CounterImpl;
			friend struct Base::ObjectContainerAccess;
		};
	}
}