#pragma once
#include "Task.h"
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Action
	{
		class OnActionBase
		{
		protected:
			Time::Task& mp_taskRef;
			Base::ObjectContainer& mp_worldRef;
		public:
			template<class TaskType>
			OnActionBase(Base::ObjectContainer& world, const TaskType& task);
		};
	}
}

