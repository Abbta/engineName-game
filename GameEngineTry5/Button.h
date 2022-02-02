#pragma once
#include "Rectangle.h"
#include "OnClick.h"
#include "ObjectContainerAccess.h"
namespace EngineName
{
    namespace Time
    {
        class Move;
    }
    namespace Object
    {
        class ButtonConstructor;
        class TextButtonConstructor;

        class Button :
            virtual public Rectangle
        {
        private:
            Action::OnClick &mp_actionRef;
            void mpf_changeOnClickArea(Visible& newArea);
        public:
            template<class T>
            Button(const Rectangle& rect, const T& onClickTask)
                :Rectangle(rect), mp_actionRef(Base::ObjectContainerAccess::getActionListener(*mptr_world).addClickListener(Action::OnClick(mptr_world, onClickTask, this)))
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
            friend class TextButtonConstructor;
        };
    }
}

