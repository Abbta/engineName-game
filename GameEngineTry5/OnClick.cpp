#include "OnClick.h"
#include "ObjectContainerAccess.h"
namespace EngineName
{
	namespace Action
	{
		bool OnClick::onClick(const unsigned int x, const unsigned int y)
		{
			if (!mp_toggle)
				return false;

			auto activeScene = Base::ObjectContainerAccess::getActiveScene(mp_worldRef);
			if (activeScene)
				if (!activeScene->contains(*mpptr_area))
					//if there is an active scen but it doesnt contain are
					return false;
				//if the area is on screen
			if ((*mpptr_area).boxContains(Object::Vector(x, y)))
			{
				//and click is within it
				mpf_schedule(mp_worldRef, *mpptr_task);
				return true;
			}
			return false;
		}

		void OnClick::mpf_changeArea(const Object::Visible& newArea)
		{
			mpptr_area = &newArea;
		}
	}
}