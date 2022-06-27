#include "Task.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		struct ObjectContainerAccess;
	}
	namespace Action
	{
		class OnActionBase;
	}
	namespace Object
	{
		template<class t_CountType, class t_TaskType> class CounterImpl;
	}
	namespace Time
	{
		/*
		* Taskcontainer class
		* stores all tasks, as their common base class
		*/
		class TaskContainer
		{
		private:
			friend class Base::ObjectContainer;
			friend struct Base::ObjectContainerAccess;
			friend class Action::OnActionBase;
			template<class t_CountType, class t_TaskType> friend class Object::CounterImpl;

			//list containing all tasks
			std::list<std::unique_ptr<Task>> mparr_allTasks;

			//Templated function that can build any type of task
			template<class t_taskType>
			t_taskType& mpf_add(const t_taskType& task)
			{
				//dynamically allocates a new task
				auto newTaskPtr = new t_taskType(task);
				//add a pointer to Task base class part in allTasks
				mparr_allTasks.push_back(std::unique_ptr<Task>(newTaskPtr));
				//sets references to list and iterator inside the task
				newTaskPtr->mptr_storageRef = &mparr_allTasks;
				std::list<std::unique_ptr<Task>>::iterator it = mparr_allTasks.end();
				it--;
				newTaskPtr->mpit_storageItRef = it;
				//return ptr to task
				return *newTaskPtr;
			}

			//assumes argument is a dynamically allocated child of task that has been downcast to Task
			Task* mpf_addAlreadyAllocated(Task* dynamicallyAllocatedTask)
			{
				//take ownership of dynamically allocated memory
				mparr_allTasks.push_back(std::unique_ptr<Task>(dynamicallyAllocatedTask));
				//init references to list and iterator
				dynamicallyAllocatedTask->mptr_storageRef = &mparr_allTasks;
				std::list<std::unique_ptr<Task>>::iterator it = mparr_allTasks.end();
				it--;
				dynamicallyAllocatedTask->mpit_storageItRef = it;
				//return
				return dynamicallyAllocatedTask;
			}
		};
	}
}