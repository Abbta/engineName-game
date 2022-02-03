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
		template<class t_CountType, class t_TaskType> class Counter;
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

		template<typename t_CountType>
		class UpdateDisplay : public Task
		{
		private:
			std::list<UpdateDisplay<t_CountType>>* mptr_storageRef;
			std::list<UpdateDisplay<int>>::iterator mpit_storageItRef;
			
			Object::Display<t_CountType>& mp_displayRef;
			Object::Counter<t_CountType, UpdateDisplay<t_CountType>>& mp_counterRef;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				mp_displayRef.mp_updateDisplay(mp_counterRef);
			}

			virtual void Destroy() override
			{
				if (mp_isDestructable)
					mptr_storageRef->erase(mpit_storageItRef);
			}
		public:
			UpdateDisplay(Object::Display<t_CountType>& display) :
				mp_displayRef(display), mptr_storageRef(nullptr)
			{

			}
			friend class TaskContainer;
		};
	}
}