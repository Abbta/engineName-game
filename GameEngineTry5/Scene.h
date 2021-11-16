#pragma once
#include "ObjectGroup.h"
#include "VisibleGroup.h"
namespace EngineName
{
    namespace Object
    {
        class Scene :
            public ObjectGroup
        {
        private:
            std::unique_ptr<VisibleGroup> mptr_visibleGroup;
        public:
            Scene(Base::ObjectContainer& world);
            Scene(const Scene& scene);

            Visible& add(Visible& visible);
            VisibleGroup& mf_getVisibles();
        };

    }
}

