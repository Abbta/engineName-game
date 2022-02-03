#include "Object.h"
#include "ObjectContainerAccess.h"
#pragma once
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Time
    {
        class Task;
        class TaskContainer;
        template<typename t_CountType> class UpdateDisplay;
    }
    namespace Object
    {
        template<class t_CountType> class Display;

        template<class t_CountType, class t_TaskType>
        class Counter :
            public Object
        {
        private:
            t_CountType mp_count;
            Time::Task* mptr_onCountChange;
        public:
            Counter(Base::ObjectContainer &world, const t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr):
                Object(world), mp_count(initialCount), mptr_onCountChange(nullptr)
            {
                if (onCountChange)
                {
                    mptr_onCountChange = &Base::ObjectContainerAccess::getTaskContainer(world).mpf_add(*onCountChange);
                    mptr_onCountChange->makeIndestructable();
                }
            }

            template<class t_CountType> friend class Display;

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
                return Counter += static_cast<t_CountType>(1);
            }

            Counter& operator-=(const t_CountType& amount)
            {
                return Counter += (-amount);
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
            }
        };
    }
}

