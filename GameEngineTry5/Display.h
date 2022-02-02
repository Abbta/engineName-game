#include "TextRectangle.h"
#include "Counter.h"
#pragma once
namespace EngineName
{
    namespace Time
    {
        template<typename t_CountType> class UpdateDisplay;
    }
    namespace Object
    {
        template<class t_CountType> class Display;

        template<typename t_CountType>
        Counter<t_CountType, Time::UpdateDisplay<t_CountType>> inlinef_buildCounter(Base::ObjectContainer& world, Display<t_CountType>* thisPtr, t_CountType initialCount);

        template<class t_CountType>
        class Display :
            public TextRectangle
        {
        private:
            Counter<t_CountType, Time::UpdateDisplay<t_CountType>>* mptr_counter;
            void mp_updateDisplay(t_CountType newCount);
        public:
            Display(TextRectangle& textRectangle, const t_CountType initialCount = 0)
                :TextRectangle(textRectangle), Rectangle(textRectangle), mptr_counter(nullptr)
            {
                mptr_counter = &inlinef_buildCounter(mptr_world, this, initialCount);
            }
        };
    }
}

#include "Display.inl"