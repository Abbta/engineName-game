#pragma once
#include "Display.h"
#include "CounterConstructor.h"
#include "CounterTasks.h"
namespace EngineName
{
	namespace Object
	{
        template<class t_CountType>
        class DisplayImpl :
            public Display
        {
        private:
            virtual void mp_updateDisplay(const Counter& newCount) override
            {
                const CounterImpl<t_CountType, Time::UpdateDisplay>& downCast = dynamic_cast<const CounterImpl<t_CountType, Time::UpdateDisplay>&>(newCount);
                //throws std::bad_cast

                mp_updateDisplay(downCast.count());
            }

            template<class t_CountType> void mp_updateDisplay(const t_CountType& newCount)
            {
                //count has changed, redraw display
                TextRectangle::mp_text = std::to_wstring(newCount);
                Base::ObjectContainerAccess::drawVisible(*mptr_world, *this);
            }
        public:
            DisplayImpl(const Display& display, const t_CountType initialCount = 0)
                :Display(display), Rectangle(display)
            {
                //build a counter and store its ptr in mptr_counter
                const Time::UpdateDisplay tempTask = Time::UpdateDisplay(*this);
                mptr_counter = &Base::ObjectContainerAccess::getCounter(*mptr_world).build<t_CountType, Time::UpdateDisplay>(*mptr_world, initialCount, &tempTask);
                auto counterImplPtr = dynamic_cast<CounterImpl<t_CountType, Time::UpdateDisplay>*>(mptr_counter);
                if (counterImplPtr == nullptr)
                    throw Exceptions::BasicException("Counter is not of correct type");
                auto taskPtr = dynamic_cast<Time::UpdateDisplay*>(counterImplPtr->mptr_onCountChange);
                if (taskPtr == nullptr)
                    throw Exceptions::BasicException("Counter task is not UpdateDisplay");
                taskPtr->m_updateCounterPtr(*mptr_counter);
            }
        };
	}
}