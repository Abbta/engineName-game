#pragma once
#include "ObjectGroup.h"
namespace EngineName
{
    namespace Object
    {
        class Scene :
            public ObjectGroup
        {
        public:
            Scene(Base::ObjectContainer& world) : ObjectGroup(world) {};
        };

    }
}

