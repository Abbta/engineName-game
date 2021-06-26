#pragma once
#include "ObjectConstructor.h"
#include "BaseIncludeLibraries.h"
#include "Button.h"
namespace EngineName
{
    namespace Object
    {
        class ButtonConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Button>> mparr_allButtons;
        public:
            ButtonConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {};
            ButtonConstructor(Base::ObjectContainer* world) : ObjectConstructor(*world) {};

            Button& build(const Button& button);
        };
    }
}
