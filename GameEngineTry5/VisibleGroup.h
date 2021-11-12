#pragma once
#include "Object.h"
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        class VisibleGroup :
            public Object
        {
        protected:
            std::vector<Visible*> mparr_visiblePointers;
        public:
            VisibleGroup(Base::ObjectContainer& world) : Object(world) {}

            Visible& add(Visible& visible);
        };
    }
}


