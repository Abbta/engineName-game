#include "OnActionBase.h"
#include "Queue.h"
#include "ObjectContainerAccess.h"
#define queue Base::ObjectContainerAccess::getQueue(world)
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
			queue.mpf_addToQueue(task);
		}
	}
}