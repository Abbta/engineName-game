#pragma once
#include "Queue.h"
#include "Counter.h"
namespace EngineName
{
	namespace Object
	{
        template<class t_CountType> class DisplayImpl;

        /*
        * Counter Implemented template class
        * Implemented part of counter
        * Contains count of t_CountType type
        * Contains a ptr to a task with t_TaskType class
        * Handles requests to change count, schedules task when this happens
        */
        template<class t_CountType, class t_TaskType>
        class CounterImpl :
            public Counter
        {
        private:
            t_CountType mp_count;
            //task will schedule when count changes
                //Counter works a bit like an OnAction
                //meaning it handles scheduling itself
                //but the task is stored in TaskContainer
            Time::Task* mptr_onCountChange;
        protected:
            //requests to increment goes via Counter base class to this method
            virtual void mpf_increment(const void* amount) override
            {
                //note the use of void*
                    //this is due to the method having to be virtual
                    //meaning it can not be templated
                //this might cause issues and TODO is to solve this
                    //or atleast error check it in a good way
                    //or make the classes keep track of what types they are counting with

                auto ptr_countTypeAmount = static_cast<const t_CountType*>(amount);
                //atleast check that it is a valid ptr
                if (ptr_countTypeAmount = nullptr)
                {
                    throw Exceptions::BasicException("Invald amount in increment counter");
                }
                increment(*ptr_countTypeAmount);
                //potential crash point, no idea what comes in and no idea what goes out
            }
        public:
            CounterImpl(Base::ObjectContainer& world, const t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr) :
                Counter(world), mp_count(initialCount), mptr_onCountChange(nullptr)
            {
                //nullptr in onCountChange means that nothing should happen at count change
                if (onCountChange)
                {
                    mptr_onCountChange = &Base::ObjectContainerAccess::getTaskContainer(world).mpf_add<t_TaskType>(onCountChange);
                    mptr_onCountChange->makeIndestructable();
                }
            }

            const t_CountType count() const
            {
                return mp_count;
            }

            template<class t_CountType> friend class DisplayImpl;

            //when incremented, task will schedule
            const t_CountType increment(const t_CountType& amount)
            {
                mp_count += amount;
                if (mptr_onCountChange)
                {
                    Base::ObjectContainerAccess::getQueue(*mptr_world).mpf_addToQueue(*mptr_onCountChange);
                }
                return mp_count;
            }

            //when set to a different value, task will schedule
            const t_CountType set(const t_CountType& newCount)
            {
                if (mp_count != newCount)
                {
                    mp_count = newCount;
                    if (mptr_onCountChange)
                        Base::ObjectContainerAccess::getQueue(*mptr_world).mpf_addToQueue(*mptr_onCountChange);
                }
                return mp_count;
            }
            //TODO: operators
            /*
            Counter& operator=(const t_CountType& newCount)
            {
                set(newCount);
                return *this;
            }

            Counter& operator+=(const t_CountType& amount)
            {
                increment(amount);
                return *this;
            }

            Counter& operator++()
            {
                return *this += static_cast<t_CountType>(1);
            }

            Counter& operator-=(const t_CountType& amount)
            {
                return *this += (-amount);
            }

            const t_CountType operator-() const
            {
                return -mp_count;
            }

            const t_CountType operator+ (const t_CountType value) const
            {
                return mp_count + value;
            }

            const t_CountType operator- (const t_CountType value) const
            {
                return mp_count - value;
            }*/
        };
	}
}