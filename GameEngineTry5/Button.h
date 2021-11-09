#pragma once
#include "Rectangle.h"
#include "OnClick.h"
namespace EngineName
{
    namespace Time
    {
        class Move;
    }
    namespace Object
    {
        class ButtonConstructor;

        class Button :
            public Rectangle
        {
        private:
            Action::OnClick &mp_actionRef;
            static Action::ActionListener& msp_getActionListener(Base::ObjectContainer* worldPtr);
            void mpf_changeOnClickArea(Visible& newArea);
        public:
            template<class T>
            Button(const Rectangle& rect, const T& onClickTask)
                :Rectangle(rect), mp_actionRef(msp_getActionListener(mptr_world).addClickListener(Action::OnClick(mptr_world, onClickTask, this)))
            {
                //as button reuses task, it should not be destroyed
                mp_actionRef.mpptr_task->makeIndestructable();
            }

            //T should be same as original T
            template<class T>
            void changeOnClickTask(const T& newTask)
            {
                mp_actionRef.mpf_changeTask(newTask);
                //as button reuses task, it should not be destroyed
                mp_actionRef.mpptr_task->makeIndestructable();
            }

            friend class ButtonConstructor;
        };
    }
}
