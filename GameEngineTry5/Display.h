#include "TextRectangle.h"
#include "BasicException.h"
#pragma once
namespace EngineName
{
    namespace Time
    {
        class UpdateDisplay;
    }
    namespace Object
    {
        class Counter;

        /*
        * Display class
        * Parent of displayImpl which handles construction
        *   and display update
        * 
        * Is essentially a textrectangle with a counter associated
        *   with it, accessed via mptr_
        */
        class Display :
            public TextRectangle
        {
        protected:
            //is actually counterImpl
            Counter* mptr_counter;

            //counter signals that it has been changed
            virtual void mp_updateDisplay(const Counter& newCount)
            {
                throw Exceptions::BasicException("Error, mp_updateDisplay accesed from Display base class");
            }
        public:
            Display(const TextRectangle& textrectangle):
                TextRectangle(textrectangle), Rectangle(textrectangle), mptr_counter(nullptr) {}

            //get the counter associated with the display
            Counter& counter()
            {
                return *mptr_counter;
            }

            friend class Time::UpdateDisplay;
        };
    }
}