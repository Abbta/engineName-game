#pragma once
#include "ObjectConstructor.h"
#include "Counter.h"
namespace EngineName
{
    namespace Object
    {
        class CounterConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Counter<int, void>>> mparr_intVoidCounters;
            std::list<std::unique_ptr<Counter<int, Time::UpdateDisplay<int>>>> mparr_intDisplayCounters;
        public:
            CounterConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {}
            CounterConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            Counter<int, void>& build(const Counter<int, void>& counter)
            {
                mparr_intVoidCounters.push_back(std::make_unique<Counter<int, void>>(counter));
                return *mparr_intVoidCounters.back();
            }

            Counter<int, Time::UpdateDisplay<int>>& build(const Counter<int, Time::UpdateDisplay<int>>& counter)
            {
                mparr_intDisplayCounters.push_back(std::make_unique<Counter<int, Time::UpdateDisplay<int>>>(counter));
                return *mparr_intDisplayCounters.back();
            }
        };
    }
}


