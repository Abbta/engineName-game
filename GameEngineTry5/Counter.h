#include "Object.h"
#include "ObjectContainerAccess.h"
#include "BasicException.h"
#pragma once
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Time
    {
        class UpdateDisplay;
    }
    namespace Object
    {
       class Display;

        class Counter :
            public Object
        {
        protected:
            virtual void mpf_increment(const void* amount);
        public:
            Counter(Base::ObjectContainer& world):
                Object(world) {}

            template<class t_CountType> Counter& operator+=(const t_CountType& amount)
            {
                const t_CountType* amountPtr = &amount;
                mpf_increment(amountPtr);
                return *this;
            }

        };

    }
}

