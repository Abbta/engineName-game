#pragma once
#include "TextRectangle.h"
#include "Counter.h"
namespace EngineName
{
    namespace Object
    {
        template<class t_CountType>
        class Display :
            public TextRectangle
        {
        private:
            Counter<t_CountType, void>& mp_counter;
        public:
            Display(TextRectangle& textRectangle, t_CountType initialCount = 0)
                :TextRectangle(textRectangle), mp_counter(mptr_world->counter.build(Counter<t_CountType, void>(*mptr_world, initialCount))))
            {

            }
        };
    }
}


