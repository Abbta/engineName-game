#pragma once
#include "Task.h"
#include "DevDefinedTasks.h"
#include "ObjectContainerAccess.h"
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
			Time::Task* mpptr_task;
			Base::ObjectContainer& mp_worldRef;
			void mpf_schedule(Base::ObjectContainer& world, Time::Task& task);
			template<class T>
			void mpf_changeTask(const T& newTask)
			{
				(*mpptr_task).Destroy();
				mpptr_task = Base::ObjectContainerAccess::getTaskContainer(mp_worldRef).mpf_add(newTask);
			}
		public:
			template<class TaskType>
			OnActionBase(Base::ObjectContainer& world, const TaskType& task)
				:mp_worldRef(world), mpptr_task(&Base::ObjectContainerAccess::getTaskContainer(world).mpf_add(task))
			{
			}

			friend class Object::Button;
		};
	}
}

