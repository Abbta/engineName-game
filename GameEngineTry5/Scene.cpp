#include "Scene.h"
namespace EngineName
{
    namespace Object
    {
        Scene::Scene(Base::ObjectContainer& world) : ObjectGroup(world), mptr_visibleGroup(std::make_unique<VisibleGroup>(world)) 
        {

        }

        VisibleGroup& Scene::mf_getVisibles()
        {
            return *mptr_visibleGroup;
        }

        Visible& Scene::add(Visible& visible)
        {
            return mptr_visibleGroup->add(visible);
            //ObjectGroup::add(visible); //may not be needed
        }
    }
}