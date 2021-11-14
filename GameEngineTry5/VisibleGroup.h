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
            Visible& getFromID(const PaintingOrder& id) { int a = 0; return getFromID(id, a); }
            Visible& getFromID(const PaintingOrder& id, int& lastIndex);
            Visible* operator[](const int index) { return mparr_visiblePointers.at(index); }
            size_t size() const { return mparr_visiblePointers.size(); }
        };
    }
}


