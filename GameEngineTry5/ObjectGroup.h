#pragma once
#include "Object.h"
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Object
    {
        /*
        * (Used to group objects)
        */
        class ObjectGroup :
            public Object
        {
        protected:
            std::vector<Object*> mparr_objectPointers;
        public:
            ObjectGroup(Base::ObjectContainer& world) : Object(world) {};

            Object& add(Object& object);
        };
    }
}


