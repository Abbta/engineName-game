#include "ObjectTasks.h"
#include "Rectangle.h"
#include "Circle.h"
namespace EngineName
{
	namespace Time
	{

		Move::Move(Object::Visible& visible, const Object::Vector& direction) : mpc_visible(visible), mpv_direction(direction)
		{
		}

		void Move::mpf_perform(Base::ObjectContainer& world)
		{
			mpc_visible.translate(mpv_direction);
			mpc_visible.draw();
		}
	}
}