#pragma once
#include "Rectangle.h"
#include "OnClick.h"
namespace EngineName
{
    namespace Object
    {
        class Button :
            public Rectangle
        {
        private:
            Action::OnClick &mp_actionRef;
        public:
            Button(const Rectangle& rect, const Action::OnClick& action);
        };
    }
}

