#include "OnActionBase.h"
#include "Queue.h"
#include "ObjectContainerAccess.h"
#define queue Base::ObjectContainerAccess::getQueue(world)
namespace EngineName
{
	namespace Action
	{
		void OnActionBase::mpf_schedule(Base::ObjectContainer& world, Time::Task& task)
		{
			queue.mpf_addToQueue(task);
		}
	}
}