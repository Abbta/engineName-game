#pragma once
#include "Display.h"
#include "CounterConstructor.h"
#include "CounterTasks.h"
namespace EngineName
{
	namespace Object
	{
        /*
        * DisplayImpl template class
        * Implemented part of display
        * Handles construction of counter member
        * Handles display updates
        */
        template<class t_CountType>
        class DisplayImpl :
            public Display
        {
        private:
            //updates display to match newCount param
            //takes Counter as param insted of the actual count as counter
                //has a constant type which avoids templatisation
            //however this might cause errors if CounterImpl part of counter is of unexpected type
            virtual void mp_updateDisplay(const Counter& newCount) override
            {
                //cast to counterImpl with type matching displayImpl
                const CounterImpl<t_CountType, Time::UpdateDisplay>& downCast = dynamic_cast<const CounterImpl<t_CountType, Time::UpdateDisplay>&>(newCount);
                //throws std::bad_cast

                //calls overloaded function which does the actual updating
                mp_updateDisplay(downCast.count());
            }

            //does the actual updating, now has t_CountType param
            template<class t_CountType> void mp_updateDisplay(const t_CountType& newCount)
            {
                //todo, template specialisation for specific types (i.e how should display handle double and float)
                
                //count has changed, update output text
                TextRectangle::mp_text = std::to_wstring(newCount);
                //redraw self
                Base::ObjectContainerAccess::drawVisible(*mptr_world, *this);
            }
        public:
            /*
            * A complete display consists of five parts:
            *   Untemplated part of display which contains the visible part
            *   Implemented part of display which handles updates, child of Display
            *   Untemplated part of counter which works as a common type for all types of counter, member of Display
            *   Implemented part of counter which keeps track of count, child of Counter  
            *   Update display task, used by counter to tell display that it has updated, member of counter
            * 
            *   This constructor is responsible for the construction of all this
            */
            DisplayImpl(const Display& display, const t_CountType initialCount = 0)
                :Display(display), Rectangle(display)
            {
                //update display task which updates this 
                const Time::UpdateDisplay tempTask = Time::UpdateDisplay(*this);
                //build a counter with a updateDisplay task
                mptr_counter = &Base::ObjectContainerAccess::getCounter(*mptr_world).build<t_CountType, Time::UpdateDisplay>(*mptr_world, initialCount, &tempTask);
                //get impl part of counter
                auto counterImplPtr = dynamic_cast<CounterImpl<t_CountType, Time::UpdateDisplay>*>(mptr_counter);
                //make sure impl has correct type (honestly not sure how this can go wrong)
                if (counterImplPtr == nullptr)
                    throw Exceptions::BasicException("Counter is not of correct type");
                //get the taskptr from counter
                auto taskPtr = dynamic_cast<Time::UpdateDisplay*>(counterImplPtr->mptr_onCountChange);
                //check that no lesser intelligence has ruined the code
                if (taskPtr == nullptr)
                    throw Exceptions::BasicException("Counter task is not UpdateDisplay");
                //connect the updateDisplay to correct counter
                taskPtr->m_updateCounterPtr(*mptr_counter);
            }
        };
	}
}