#pragma once
#include "OnActionBase.h"
#include "Visible.h"
namespace EngineName
{
    namespace Action
    {
        template<class TaskType>
        class OnClick :
            public OnActionBase<TaskType>
        {
        private:
            Object::Visible& mp_areaRef;
        public:
            OnClick(TaskType& task, Object::Visible& area): OnActionBase<TaskType>(task), mp_areaRef(area) {}
        };
    }
}
