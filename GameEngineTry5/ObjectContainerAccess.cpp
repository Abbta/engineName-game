#include "ObjectContainerAccess.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Base
	{
		Drawing::Painter& ObjectContainerAccess::getPainter(ObjectContainer& world)
		{
			return *(world.mpptr_window->mpptr_painter);
		}

		Time::TaskContainer& ObjectContainerAccess::getTaskContainer(ObjectContainer& world)
		{
			return world.mpc_theQueue.mpc_taskContainer;
		}

		Time::Queue& ObjectContainerAccess::getQueue(ObjectContainer& world)
		{
			return world.mpc_theQueue;
		}

		Action::ActionListener& ObjectContainerAccess::getActionListener(ObjectContainer& world)
		{
			return world.mp_actionListener;
		}

		WindowAccess& ObjectContainerAccess::getWindowAccessor(ObjectContainer& world)
		{
			return world.window;
		}

		Width& ObjectContainerAccess::getWidth(ObjectContainer& world)
		{
			return world.width;
		}

		Height& ObjectContainerAccess::getHeight(ObjectContainer& world)
		{
			return world.height;
		}

		Time::Task* ObjectContainerAccess::mpf_scheduleImpl(ObjectContainer& world, Time::Task* dynamicallyAllocatedTask, const int ms)
		{
			auto taskRef = getTaskContainer(world).mpf_addAlreadyAllocated(dynamicallyAllocatedTask);

			taskRef->addTimeLeftInQueue(std::chrono::milliseconds(ms));

			getQueue(world).mpf_addToQueue(*taskRef);

			return taskRef;
		}
	}
}