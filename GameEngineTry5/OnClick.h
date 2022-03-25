#pragma once
#include "OnActionBase.h"
#include "Visible.h"
#include "ObjectTasks.h"
#include "DevDefinedTasks.h"
namespace EngineName
{
    namespace Object
    {
        class Button;
    }
    namespace Action
    {
        class ActionListener;

        class OnClick :
            public OnActionBase
        {
        private:
            bool mp_toggle;
            Object::Visible* mpptr_area;
            void mpf_changeArea(Object::Visible& newArea);
        public:
            template<class TaskType>
            OnClick(Base::ObjectContainer& world, const TaskType& task, Object::Visible& area)
                : OnActionBase(world, task), mpptr_area(area), mp_toggle(true) {}

            
            template<class TaskType>
            OnClick(Base::ObjectContainer* world, const TaskType& task, Object::Visible* area)
                : OnActionBase(*world, task), mpptr_area(area), mp_toggle(true) {}
                
            bool onClick(const unsigned int x, const unsigned int y);

            friend class ActionListener;
            friend class Object::Button;
            friend class Object::ActivatableTButton;
        };
    }
}
