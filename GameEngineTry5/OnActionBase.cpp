#include "OnActionBase.h"
#include "Queue.h"
#include "ObjectContainerAccess.h"
#define queue Base::ObjectContainerAccess::getQueue(world)
namespace EngineName
{
	namespace Action
	{
		template<class TaskType>
		OnActionBase::OnActionBase(Base::ObjectContainer& world, const TaskType& task)
			:mp_worldRef(world)
		{
			mp_taskRef = queue.mpc_taskContainer.mpf_add<TaskType>(task);
		}

		void OnActionBase::mpf_schedule(Base::ObjectContainer& world, Time::Task& task)
		{
			queue.mpf_addToQueue(task);
		}
	}
}