#include "ObjectTasks.h"
#include "Rectangle.h"
#include "Circle.h"
#include "ObjectContainer.h"
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

		ChangeActiveScene::ChangeActiveScene(Object::Scene& newScene)
			:mpc_newScene(newScene)
		{

		}

		void ChangeActiveScene::mpf_perform(Base::ObjectContainer& world)
		{
			world.setActiveScene(mpc_newScene);
		}

		ToggleATButton::ToggleATButton(Object::ActivatableTButton& activatableTButton)
			:mpc_aTButton(activatableTButton)
		{

		}

		void ToggleATButton::mpf_perform(Base::ObjectContainer& world)
		{
			mpc_aTButton.toggleActive();
			Base::ObjectContainerAccess::drawVisible(world, mpc_aTButton);
		}
	}
}