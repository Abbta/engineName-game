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
		/*
		* Move task
		* translates all points of a visible in accordance to a vector
		*/
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

		/*
		* Change active scene task
		* makes a scene being considered active by painter
		*	meaning only its memebers will be displayed on screen
		*/
		class ChangeActiveScene : public Task
		{
		private:
			virtual void mpf_perform(Base::ObjectContainer& world) override;

			Object::Scene& mpc_newScene;
		public:
			ChangeActiveScene(Object::Scene& newScene);
			friend class TaskContainer;
		};

		/*
		* Toggle activatable text button task
		* toggles a aTButton from either being 
		*	active to inactive or vice versa
		*		inactive meaning unclickable
		*/
		class ToggleATButton : public Task
		{
		private:
			virtual void mpf_perform(Base::ObjectContainer& world) override;

			Object::ActivatableTButton& mpc_aTButton;
		public:
			ToggleATButton(Object::ActivatableTButton& activatableTButton);
			friend class TaskContainer;
		};
	}
}