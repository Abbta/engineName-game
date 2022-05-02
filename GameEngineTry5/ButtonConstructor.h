#pragma once
#include "ObjectConstructor.h"
#include "BaseIncludeLibraries.h"
#include "Button.h"
namespace EngineName
{
    namespace Object
    {
        /*
       * Button constructor class
       * Used for constructing button
       * Has .build()
       *   constructs the object
       *   gives back ref
       * Stores all buttons within itself
       */
        class ButtonConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Button>> mparr_allButtons;
        public:
            //button constructor is constructed in world which sends this as param
            ButtonConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

            Button& build(const Button& button);
        };
    }
}
