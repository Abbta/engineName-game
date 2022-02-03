#pragma once
#include "ObjectConstructor.h"
#include "Display.h"
namespace EngineName
{
    namespace Object
    {
        class DisplayConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Display<int>>> mparr_intDisplays;
        public:
            DisplayConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {};
            DisplayConstructor(Base::ObjectContainer* world) : ObjectConstructor(*world) {};

            Display<int>& build(const Display<int>& display);
        };
    }
}

