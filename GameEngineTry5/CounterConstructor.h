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
        public:
            CounterConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {}
            CounterConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            Counter<int, void>& build(const Counter<int, void>& counter)
            {
                mparr_intVoidCounters.push_back(std::make_unique<Counter<int, void>>(counter));
                return *mparr_intVoidCounters.back();
            }
        };
    }
}


