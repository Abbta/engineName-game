#include "ObjectTasks.h"
#include "Rectangle.h"
#include "Circle.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Time
	{
		//Move
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

		//ChangeActiveScene
		ChangeActiveScene::ChangeActiveScene(Object::Scene& newScene)
			:mpc_newScene(newScene)
		{

		}

		void ChangeActiveScene::mpf_perform(Base::ObjectContainer& world)
		{
			Drawing::Painter& painterRef = world.mpf_getPainter();
			painterRef.mf_changeActiveScene(mpc_newScene.mf_getVisibles());
			painterRef.mf_drawAll();
		}

		void ChangeActiveScene::Destroy()
		{
			if (mp_isDestructable)
				mptr_storageRef->erase(mpit_storageItRef);
		}
	}
}