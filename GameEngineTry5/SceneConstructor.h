#pragma once
#include "ObjectConstructor.h"
#include "Scene.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * sceneconstructor class
        * used for constructing scenes
        * has .build()
        *   constructs the object
        *   gives back ref
        * stores all scenes within itself
        */
        class SceneConstructor :
            public ObjectConstructor
        {
        private:
            //stores all scenes
            std::list<std::unique_ptr<Scene>> mparr_allScenes;
        public:
            SceneConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

            //constructs a new scene
            Scene& build(Base::ObjectContainer& world);
        };
    }
}


