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
	}
}