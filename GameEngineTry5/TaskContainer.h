#pragma once
namespace EngineName
{
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
			friend class Action::OnActionBase;
		};
	}
}