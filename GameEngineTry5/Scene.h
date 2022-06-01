#pragma once
#include "ObjectGroup.h"
#include "VisibleGroup.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * Scene class
        *   Is an objectgroup with a visiblegroup as member
        *   Keeps track of what objects and visibles that should be regarded as active
        */
        class Scene :
            public ObjectGroup
        {
        private:
            std::unique_ptr<VisibleGroup> mptr_visibleGroup;
        public:
            Scene(Base::ObjectContainer& world);
            Scene(const Scene& scene);

            //adds a visible to the scene
            Visible& add(Visible& visible);

            //gets visiblegroup of visibles in scene
            VisibleGroup& mf_getVisibles();
        };

    }
}

