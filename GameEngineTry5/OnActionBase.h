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
		/*
		* On action base class
		* Is base class for all on actions
		*	i.e classes that corresponds to actionlisteners for example OnClick
		*		which corresponds to listening for clicks in actionlistener
		* with it is an associated task that is performed when action occurs
		*/
		class OnActionBase
		{
		protected:
			//ptr to task, task itself is stored in taskcontainer and can be of any task type
			Time::Task* mpptr_task;
			Base::ObjectContainer& mp_worldRef;
			//when action happens it schedules task via this function instead of via objectContainerAccess
			virtual void mpf_schedule(Base::ObjectContainer& world, Time::Task& task);
			//change task, template since new task can be any kind of task
			template<class T>
			void mpf_changeTask(const T& newTask)
			{
				//might give unexpected behaviour if newTask is not a task

				//remove current task
				(*mpptr_task).mpf_destroyIndestructible();

				//add a new one
				mpptr_task = Base::ObjectContainerAccess::getTaskContainer(mp_worldRef).mpf_add(newTask);
				mpptr_task->makeIndestructable();
			}
		public:
			template<class TaskType>
			OnActionBase(Base::ObjectContainer& world, const TaskType& task)
				:mp_worldRef(world), mpptr_task(&Base::ObjectContainerAccess::getTaskContainer(world).mpf_add(task))
			{
				//tasks are normally destroyed after they are performed but a task connected to a onaction
					//is reused and the ontask should decide when it is destroyed
				//makeIndestructive() prohibits the task from destroying itself
				mpptr_task->makeIndestructable();
			}

			//TODO handle destruction of onaction, should be handled by actionlistener, remember to destroy task

			friend class Object::Button;
		};
	}
}

