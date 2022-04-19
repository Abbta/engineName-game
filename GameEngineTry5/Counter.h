#include "Object.h"
#include "ObjectContainerAccess.h"
#include "BasicException.h"
#pragma once
namespace EngineName
{
    namespace Object
    {
        /*
        * Counter class
        * Base class of counterImpl which is templated and contains the implmented part of counter
        * This type of structure is used to be able to store all types of counters in the same list
        * Is essentialy a pure virtual base class
        */
        class Counter :
            public Object
        {
        protected:
            //will throw if called in this class
            virtual void mpf_increment(const void* amount);
        public:
            Counter(Base::ObjectContainer& world):
                Object(world) {}

            //count is incremented via this public operator
            template<class t_CountType> Counter& operator+=(const t_CountType& amount)
            {
                const t_CountType* amountPtr = &amount;
                mpf_increment(amountPtr);
                return *this;
            }

        };
    }
}

