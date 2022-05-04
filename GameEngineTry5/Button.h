#pragma once
#include "Rectangle.h"
#include "OnClick.h"
#include "ObjectContainerAccess.h"
namespace EngineName
{
    namespace Action
    {
        class ActionListener;
        class OnClick;
    }
    namespace Object
    {
        class ButtonConstructor;
        class TextButtonConstructor;

        /* Button class
        *   Rectangle with an OnClick associated with it
        *   Inherits Rectangle virtually due to diamond inheritance with TextButton
        */
        class Button :
            virtual public Rectangle
        {
        protected:
            //reference to the associated OnClick
            Action::OnClick &mpc_actionRef;
                /*is an actionlistener that listens for clicks in a specified areaand executes
                    a task that it handles itself
                the listener itself is stored in world but Button has responsibility for it
                button uses the ref for telling the listener to change its task
                    or area*/

            //changes area where OnClick checks for clicks
            void mpf_changeOnClickArea(const Visible& newArea);
        public:
            //note that constructor is template due to onClickTask being any Task type
            template<class t_TaskType>
            Button(const Rectangle& rect, const t_TaskType& onClickTask)
                :Rectangle(rect), 
                mpc_actionRef(
                    //add a clicklistener in world with params and keep a ref to it
                    Base::ObjectContainerAccess::getActionListener(*mptr_world).addClickListener(
                        Action::OnClick(*mptr_world, onClickTask, this)))
            {}

            //Changes task performed when OnClick triggers
            template<class t_TaskType>
            void changeOnClickTask(const t_TaskType& newTask)
            {
                mpc_actionRef.mpf_changeTask(newTask);
            }

            //TODO: handle destruction, also destructing OnClick

            friend class ButtonConstructor;
            friend class TextButtonConstructor;
        };
    }
}

