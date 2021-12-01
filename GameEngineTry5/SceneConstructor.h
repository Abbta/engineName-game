#pragma once
#include "ObjectConstructor.h"
#include "Scene.h"
namespace EngineName
{
    namespace Object
    {
        class SceneConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Scene>> mparr_allScenes;
        public:
            SceneConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

            Scene& build(Base::ObjectContainer& world);
        };
    }
}


