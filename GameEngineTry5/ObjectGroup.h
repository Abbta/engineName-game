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
        * ObjectGroup class
        * object that represents a group of other objects
        */
        class ObjectGroup :
            public Object
        {
        protected:
            //ptrs to all objects in group
            std::vector<Object*> mparr_objectPointers;
        public:
            ObjectGroup(Base::ObjectContainer& world) : Object(world) {};

            //adds an object to the group
            Object& add(Object& object);
        };
    }
}


