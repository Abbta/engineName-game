#include "ObjectTasks.h"
#include "Rectangle.h"
#include "Circle.h"
namespace EngineName
{
	namespace Time
	{

		Move::Move(Object::Visible& visible, const Object::Vector& direction) : mpc_visible(visible), mpv_direction(direction), mptr_storageRef(nullptr)
		{
		}

		void Move::mpf_perform(Base::ObjectContainer& world)
		{
			mpc_visible.translate(mpv_direction);
			mpc_visible.draw();
		}

		void Move::Destroy()
		{
			if(mp_isDestructable)
				mptr_storageRef->erase(mpit_storageItRef);
		}
	}
}