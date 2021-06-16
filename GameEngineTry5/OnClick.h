#pragma once
#include "OnActionBase.h"
#include "Visible.h"
#include "ObjectTasks.h"
#include "DevDefinedTasks.h"
namespace EngineName
{
    namespace Action
    {
        class OnClick :
            public OnActionBase
        {
        private:
            Object::Visible& mp_areaRef;
        public:
            template<class TaskType>
            OnClick(Base::ObjectContainer& world,TaskType& task, Object::Visible& area): OnActionBase<TaskType>(world, task), mp_areaRef(area) {}
        };
    }
}
