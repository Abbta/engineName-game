#pragma once
namespace EngineName
{
	namespace Action
	{
		template<class TaskType>
		class OnActionBase
		{
		private:
			TaskType mp_task;
		public:
			OnActionBase(TaskType& task): mp_task(task) {}
		};
	}
}

