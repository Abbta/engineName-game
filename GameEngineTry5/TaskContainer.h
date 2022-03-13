#include "Task.h"
#pragma once
namespace EngineName
{
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

			std::list<std::unique_ptr<Task>> mparr_allTasks;
			template<class T>
			T& mpf_add(const T& task)
			{
				auto temp = new T(task);
				mparr_allTasks.push_back(std::unique_ptr<Task>(temp));
				temp->mptr_storageRef = &mparr_allTasks;
				std::list<std::unique_ptr<Task>>::iterator it = mparr_allTasks.end();
				it--;
				temp->mpit_storageItRef = it;
				return *temp;
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
			friend class Action::OnActionBase;
		};
	}
}