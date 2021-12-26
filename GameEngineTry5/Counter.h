#pragma once
#include "Object.h"
#include "ObjectTasks.h"
#include "DevDefinedTasks.h"
#include "ObjectContainer.h"
namespace EngineName
{
    namespace Object
    {
        template<class t_CountType, class t_TaskType>
        class Counter :
            public Object
        {
        private:
            t_CountType mp_count;
            Time::Task* mptr_onCountChange;
            static Time::TaskContainer& msp_getTaskContainer(Base::ObjectContainer& world)
            {
                return world.mpc_theQueue.mpc_taskContainer;
            }
        public:
            Counter(Base::ObjectContainer &world, t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr):
                Object(world), mp_count(initialCount), mptr_onCountChange(nullptr)
            {
                if (onCountChange)
                {
                    mptr_onCountChange = &msp_getTaskContainer(world).mpf_add(*onCountChange);
                    mptr_onCountChange->makeIndestructable();
                }
            }

            const operator t_CountType() const
            {
                return mp_count;
            }

            const t_CountType set(const t_CountType& newCount = 0)
            {
                mp_count = newCount;
                if (mptr_onCountChange)
                    mptr_world->mpc_theQueue.mpf_addToQueue(*mptr_onCountChange);
                return mp_count;
            }

            const t_CountType increment(const t_CountType& amount = 1)
            {
                mp_count += amount;
                if(mptr_onCountChange)
                    mptr_world->mpc_theQueue.mpf_addToQueue(*mptr_onCountChange);
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

