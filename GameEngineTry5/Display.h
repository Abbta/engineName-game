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
        template<class t_CountType>
        class Display :
            public TextRectangle
        {
        private:
            Counter<t_CountType, Time::UpdateDisplay<t_CountType>>* mptr_counter;
            void mp_updateDisplay(t_CountType newCount)
            {
                //count has changed, redraw display
                Base::ObjectContainerAccess::drawVisible(*mptr_world, *this);
            }
            void mp_updateDisplay(Counter<t_CountType, Time::UpdateDisplay<t_CountType>>& newCount)
            {
                mp_updateDisplay(newCount.mp_count);
            }
        public:
            Display(const TextRectangle& textRectangle, const t_CountType initialCount = 0)
                :TextRectangle(textRectangle), Rectangle(textRectangle), mptr_counter(nullptr)
            {
                //build a counter and store its ptr in mptr_counter
                const Time::UpdateDisplay<t_CountType> tempTask = Time::UpdateDisplay<t_CountType>(*this);
                mptr_counter = &Base::ObjectContainerAccess::getCounter(*mptr_world).build(Counter<t_CountType, Time::UpdateDisplay<t_CountType>>(*mptr_world, initialCount, &tempTask));
            }

            template<typename t_CountType> friend class Time::UpdateDisplay;
        };
    }
}