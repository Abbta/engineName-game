#pragma once
#include "Task.h"
#include "DevDefinedTasks.h"
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		class Button;
	}
	namespace Action
	{
		class OnActionBase
		{
		protected:
			Time::Task& mp_taskRef;
			Base::ObjectContainer& mp_worldRef;
			static Time::TaskContainer& msp_getTaskContainer(Base::ObjectContainer& world);
			void mpf_schedule(Base::ObjectContainer& world, Time::Task& task);
		public:
			template<class TaskType>
			OnActionBase(Base::ObjectContainer& world, const TaskType& task)
				:mp_worldRef(world), mp_taskRef(msp_getTaskContainer(world).mpf_add(task))
			{
			}

			friend class Object::Button;
		};
	}
}

