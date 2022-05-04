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

        /*
        * OnClick OnAction
        * OnAction triggering when actionListener hears a click with left mouse button inside a specific box
        * Can be toggled to be listening or not
        */
        class OnClick :
            public OnActionBase
        {
        private:
            //toggles if onclick is active
            bool mp_toggle;
            //area is where we are listening for clicks
            Object::Visible const* mpptr_area;
            //change area changes this area
            void mpf_changeArea(const Object::Visible& newArea);
        public:
            //note that constructor is templated as task can be any type of task
            template<class TaskType>
            OnClick(Base::ObjectContainer& world, const TaskType& task, Object::Visible* area)
                : OnActionBase(world, task), mpptr_area(area), mp_toggle(true) {}
                
            //onclick is called by actionListener at every click, 
                //it is up to onClick to decide if click is valid for this onAction
            bool onClick(const td_width x, const td_height y);

            friend class ActionListener;
            friend class Object::Button;
            friend class Object::ActivatableTButton;
        };
    }
}
