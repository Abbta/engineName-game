#pragma once
#include "BaseIncludeLibraries.h"
#include "Task.h"
#include "Vector.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Scene.h"
namespace EngineName
{
	namespace Time
	{
		class Move : public Task
		{
		private:
			virtual void mpf_perform(Base::ObjectContainer& world) override;

			Object::Visible& mpc_visible;
			const Object::Vector mpv_direction;
		public:
			Move(Object::Visible& visible, const Object::Vector& direction);
			friend class TaskContainer;
		};

		class ChangeActiveScene : public Task
		{
		private:
			virtual void mpf_perform(Base::ObjectContainer& world) override;

			Object::Scene& mpc_newScene;
		public:
			ChangeActiveScene(Object::Scene& newScene);
			friend class TaskContainer;
		};
	}
}