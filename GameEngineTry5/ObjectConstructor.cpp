#include "ObjectConstructor.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		//Functions used for adding a newly consturcted visible to the array containing all visibles
		void ObjectConstructor::mf_registerNewVisible(Visible& visible)
		{
			mp_world.mparr_allVisibles.back() = &visible;
		}

		void ObjectConstructor::mf_makeRoomForNewVisible()
		{
			mp_world.mparr_allVisibles.push_back(nullptr);
		}
	}
}
