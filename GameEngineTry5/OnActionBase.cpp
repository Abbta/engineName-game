#include "OnActionBase.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Action
	{
		Time::TaskContainer& OnActionBase::msp_getTaskContainer(Base::ObjectContainer& world)
		{
			return world.mpc_theQueue.mpc_taskContainer;
		}

		void OnActionBase::mpf_schedule(Base::ObjectContainer& world, Time::Task& task)
		{
			world.mpc_theQueue.mpf_addToQueue(task);
		}
	}
}