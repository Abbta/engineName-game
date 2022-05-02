#include "ObjectConstructor.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		/*
		* make room for new visible function
		* adds an empty spot in all visibles
		* this signals that the next constructed visible is an actual unique visible with global storage
		*/
		void ObjectConstructor::mf_makeRoomForNewVisible()
		{
			mp_world.mparr_allVisibles.push_back(nullptr);
		}

		/*
		* register new visible function
		* adds visible to allVisibles, meaning it can be painted
		*/
		void ObjectConstructor::mf_registerNewVisible(Visible& visible)
		{
			mp_world.mparr_allVisibles.back() = &visible;
		}
	}
}
