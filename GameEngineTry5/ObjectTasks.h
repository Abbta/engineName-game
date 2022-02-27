#pragma once
#include "BaseIncludeLibraries.h"
#include "Task.h"
#include "Vector.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Scene.h"
#include "Display.h"
namespace EngineName
{
	namespace Object
	{
		class Counter;
	}
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

		class ChangeActiveScene : public Task
		{
		private:
			std::list<ChangeActiveScene>* mptr_storageRef;
			std::list<ChangeActiveScene>::iterator mpit_storageItRef;
			virtual void mpf_perform(Base::ObjectContainer& world) override;
			virtual void Destroy() override;

			Object::Scene& mpc_newScene;
		public:
			ChangeActiveScene(Object::Scene& newScene);
			friend class TaskContainer;
		};

		class UpdateDisplay : public Task
		{
		private:
			std::list<UpdateDisplay>* mptr_storageRef;
			std::list<UpdateDisplay>::iterator mpit_storageItRef;
			
			Object::Display& mp_displayRef;
			Object::Counter* mpptr_counter;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				mp_displayRef.mp_updateDisplay(*mpptr_counter);
			}

			virtual void Destroy() override
			{
				if (mp_isDestructable)
					mptr_storageRef->erase(mpit_storageItRef);
			}
		public:
			UpdateDisplay(Object::Display& display) :
				mp_displayRef(display), mptr_storageRef(nullptr), mpptr_counter(display.mptr_counter)
			{

			}

			void m_updateCounterPtr(Object::Counter& newCounter);
			friend class TaskContainer;
		};
	}
}