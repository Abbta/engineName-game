#pragma once
#include "Object.h"
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * VisibleGroup class
        * Group of visibles
        * has add and getters
        * does not store any visibles, just ptrs to them
        */
        class VisibleGroup :
            public Object
        {
        protected:
            //the pointers to the visibles
            std::vector<Visible*> mparr_visiblePointers;
        public:
            VisibleGroup(Base::ObjectContainer& world) : Object(world) {}

            //add a ref to the group
            Visible& add(Visible& visible);
            //getters
            Visible& getFromID(const PaintingOrder& id) { int a = 0; return getFromID(id, a); }
            Visible& getFromID(const PaintingOrder& id, int& lastIndex);
            //check if a visible is part of the group
            const bool contains(const Visible& visible) const;
            //get by [] operator
            Visible* operator[](const int index) { this; 
            return mparr_visiblePointers.at(index); }
            //get number of visibles in group
            size_t size() const { return mparr_visiblePointers.size(); }
        };
    }
}


