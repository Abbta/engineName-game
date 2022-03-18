#pragma once
#include "ObjectConstructor.h"
#include "CounterImpl.h"
namespace EngineName
{
    namespace Object
    {
        class CounterConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Counter>> mparr_allCounters;
        public:
            CounterConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {}
            CounterConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            template<class t_CountType, class t_TaskType> Counter& build(const CounterImpl<t_CountType, t_TaskType>& counter) 
            {
                CounterImpl<t_CountType, t_TaskType>* tempImplementedPart = new CounterImpl<t_CountType, t_TaskType>(counter);
                mparr_allCounters.push_back(std::unique_ptr<Counter>(tempImplementedPart));
                return *mparr_allCounters.back();
            }

            template<class t_CountType, class t_TaskType> Counter& build(Base::ObjectContainer& world, const t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr)
            {
                CounterImpl<t_CountType, t_TaskType>* tempImplementedPart = new CounterImpl<t_CountType, t_TaskType>(world, initialCount, onCountChange);
                mparr_allCounters.push_back(std::unique_ptr<Counter>(tempImplementedPart));
                return *mparr_allCounters.back();
            }
        };
    }
}


