#pragma once
#include "OnActionBase.h"
#include "Visible.h"
#include "ObjectTasks.h"
#include "DevDefinedTasks.h"
namespace EngineName
{
    namespace Action
    {
        class ActionListener;

        class OnClick :
            public OnActionBase
        {
        private:
            Object::Visible& mp_areaRef;
        public:
            template<class TaskType>
            OnClick(Base::ObjectContainer& world, const TaskType& task, Object::Visible& area)
                : OnActionBase(world, task), mp_areaRef(area) {}

            template<class TaskType>
            OnClick(Base::ObjectContainer* world, const TaskType& task, Object::Visible area)
                : OnActionBase(*world, task), mp_areaRef(area) {}
            bool onClick(const unsigned int x, const unsigned int y);

            friend class ActionListener;
        };
    }
}
