#pragma once
#include "Queue.h"
#include "Counter.h"
namespace EngineName
{
	namespace Object
	{
        template<class t_CountType> class DisplayImpl;

        template<class t_CountType, class t_TaskType>
        class CounterImpl :
            public Counter
        {
        private:
            t_CountType mp_count;
            Time::Task* mptr_onCountChange;
        protected:
            virtual void mpf_increment(const void* amount) override
            {
                increment(*static_cast<const t_CountType*>(amount));
                //potential crash point, no idea what comes in and no idea what goes out
            }
        public:
            CounterImpl(Base::ObjectContainer& world, const t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr) :
                Counter(world), mp_count(initialCount), mptr_onCountChange(nullptr)
            {
                if (onCountChange)
                {
                    mptr_onCountChange = &Base::ObjectContainerAccess::schedule(world, *onCountChange);
                    mptr_onCountChange->makeIndestructable();
                }
            }

            const t_CountType count() const
            {
                return mp_count;
            }

            template<class t_CountType> friend class DisplayImpl;

            /*const operator t_CountType() const
            {
                return mp_count;
            }*/

            const t_CountType increment(const t_CountType& amount)
            {
                mp_count += amount;
                if (mptr_onCountChange)
                    Base::ObjectContainerAccess::getQueue(*mptr_world).mpf_addToQueue(*mptr_onCountChange);
                return mp_count;
            }

            const t_CountType set(const t_CountType& newCount)
            {
                mp_count = newCount;
                if (mptr_onCountChange)
                    Base::ObjectContainerAccess::getQueue(*mptr_world).mpf_addToQueue(*mptr_onCountChange);
                return mp_count;
            }
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