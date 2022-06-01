#include "Scene.h"
namespace EngineName
{
    namespace Object
    {
        Scene::Scene(Base::ObjectContainer& world) : ObjectGroup(world), mptr_visibleGroup(std::make_unique<VisibleGroup>(world)) 
        {

        }

        Scene::Scene(const Scene& scene) : ObjectGroup(*scene.mptr_world), mptr_visibleGroup(std::make_unique<VisibleGroup>(*scene.mptr_world))
        {

        }

        VisibleGroup& Scene::mf_getVisibles()
        {
            return *mptr_visibleGroup;
        }

        Visible& Scene::add(Visible& visible)
        {
            return mptr_visibleGroup->add(visible);
            //ObjectGroup::add(visible); //may not be needed, depends on further implementation of more objects that are not visibles
        }
    }
}