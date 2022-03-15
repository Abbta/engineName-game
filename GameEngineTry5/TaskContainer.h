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
	namespace Time
	{
		class TaskContainer
		{
		private:
			friend class Base::ObjectContainer;
			friend struct Base::ObjectContainerAccess;
			friend class Action::OnActionBase;

			std::list<std::unique_ptr<Task>> mparr_allTasks;
			template<class T>
			T& mpf_add(const T& task)
			{
				auto newTaskPtr = new T(task);
				mparr_allTasks.push_back(std::unique_ptr<Task>(newTaskPtr));
				newTaskPtr->mptr_storageRef = &mparr_allTasks;
				std::list<std::unique_ptr<Task>>::iterator it = mparr_allTasks.end();
				it--;
				temp->mpit_storageItRef = it;
				return *newTaskPtr;
			}

			//assumes argument is a dynamically allocated child of task that has been downcast to Task
			Task* mpf_addAlreadyAllocated(Task* dynamicallyAllocatedTask)
			{
				//take ownership of dynamically allocated memory
				mparr_allTasks.push_back(std::unique_ptr<Task>(dynamicallyAllocatedTask));

				dynamicallyAllocatedTask->mptr_storageRef = &mparr_allTasks;
				std::list<std::unique_ptr<Task>>::iterator it = mparr_allTasks.end();
				it--;
				dynamicallyAllocatedTask->mpit_storageItRef = it;
				return dynamicallyAllocatedTask;
			}
		};
	}
}