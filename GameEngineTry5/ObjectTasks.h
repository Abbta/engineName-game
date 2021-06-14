#include "BaseIncludeLibraries.h"
#include "Task.h"
#include "Vector.h"
#include "Rectangle.h"
#include "Circle.h"
#pragma once
namespace EngineName
{
	namespace Time
	{
		class Move : public Task
		{
		private:
			std::list<Move>* mptr_storageRef;
			std::list<Move>::iterator mpit_storageItRef;
			virtual void mpf_perform(Base::ObjectContainer& world) override;
			virtual void Destroy() override;

			Object::Visible& mpc_visible;
			const Object::Vector mpv_direction;
		public:
			Move(Object::Visible& visible, const Object::Vector& direction);
			friend class TaskContainer;
		};
	}
}