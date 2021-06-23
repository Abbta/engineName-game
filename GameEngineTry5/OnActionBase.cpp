#include "OnActionBase.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Action
	{
		template<class TaskType>
		OnActionBase::OnActionBase(Base::ObjectContainer& world, const TaskType& task)
			:mp_worldRef(world)
		{
			mp_taskRef = mp_worldRef.mpc_theQueue.mpc_taskContainer.mpf_add<TaskType>(task);
		}

		void OnActionBase::mpf_schedule(Base::ObjectContainer& world, Time::Task& task)
		{
			world.mpc_theQueue.mpf_addToQueue(task);
		}
	}
}