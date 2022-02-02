#pragma once
#include "Rectangle.h"
namespace EngineName
{
    namespace Time
    {
        class Move;
    }
    namespace Action
    {
        class ActionListener;
        class OnClick;
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
            static Action::ActionListener& msp_getActionListener(Base::ObjectContainer* worldPtr);
            void mpf_changeOnClickArea(Visible& newArea);
        public:
            template<class T>
            Button(const Rectangle& rect, const T& onClickTask);

            //T should be same as T used when constructing
            template<class T>
            void changeOnClickTask(const T& newTask);

            friend class ButtonConstructor;
            friend class TextButtonConstructor;
        };
    }
}

