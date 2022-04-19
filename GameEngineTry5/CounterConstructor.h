#pragma once
#include "ObjectConstructor.h"
#include "CounterImpl.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * Counter constructor class
        * Used for constructing counter
        * Has .build()
        *   Special case:
        *       constructs the implemented object from a template dynamically
        *       demotes it to Counter base class ptr and lets a unique_ptr handle it
        *       places it in list
        *       gives back ref
        * Stores all counters within itself
        *   all counters are stored in the same list, regardless of type
        */
        class CounterConstructor :
            public ObjectConstructor
        {
        private:
            //note that the Counters are parents to CounterImpl template classes of different types
            std::list<std::unique_ptr<Counter>> mparr_allCounters;
        public:
            CounterConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            //note that build is templated
            template<class t_CountType, class t_TaskType> Counter& build(const CounterImpl<t_CountType, t_TaskType>& counter) 
            {
                //construct the actual object
                CounterImpl<t_CountType, t_TaskType>* tempImplementedPart = new CounterImpl<t_CountType, t_TaskType>(counter);
                //demote it to an object of common type and store all in the same container
                mparr_allCounters.push_back(std::unique_ptr<Counter>(tempImplementedPart));
                //return 
                return *mparr_allCounters.back();
            }

            //overload of above
            template<class t_CountType, class t_TaskType> Counter& build(Base::ObjectContainer& world, const t_CountType initialCount = 0, const t_TaskType* onCountChange = nullptr)
            {
                CounterImpl<t_CountType, t_TaskType>* tempImplementedPart = new CounterImpl<t_CountType, t_TaskType>(world, initialCount, onCountChange);
                mparr_allCounters.push_back(std::unique_ptr<Counter>(tempImplementedPart));
                return *mparr_allCounters.back();
            }
        };
    }
}


