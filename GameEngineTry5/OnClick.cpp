#include "OnClick.h"
#include "ObjectContainerAccess.h"
namespace EngineName
{
	namespace Action
	{
		/*
		* On click member function
		* is called by action listener at every click
		* coordinates of click are sent as param
		* if click was inside area associated to the on click
		*	perform task and return true
		* else returns false
		*/
		bool OnClick::onClick(const td_width x, const td_height y)
		{
			//if untoggled, no clicks count
			if (!mp_toggle)
				return false;

			//active scene are all visibles that are visible and can be clicked
			auto activeScene = Base::ObjectContainerAccess::getActiveScene(mp_worldRef);
			if (activeScene)
			//if there is an active scene
				if (!activeScene->contains(*mpptr_area))
					//if there is an active scen but it doesnt contain this area
					return false;
			
			//this is a part of active scen or there is no active scene (all visibles are active)
			//check if this area contains the coordinates of the click
			if ((*mpptr_area).boxContains(Object::Vector(x, y)))
			{
				//schedule the task
				mpf_schedule(mp_worldRef, *mpptr_task);
				return true;
			}
			//if click is not inside this area
			return false;
		}

		//changes what in what area clicks are listened for
		void OnClick::mpf_changeArea(const Object::Visible& newArea)
		{
			mpptr_area = &newArea;
		}
	}
}