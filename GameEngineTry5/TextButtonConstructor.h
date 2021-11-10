#pragma once
#include "ObjectConstructor.h"
#include "TextButton.h"
namespace EngineName
{
    namespace Object
    {
        class TextButtonConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<TextButton>> mparr_allTextButtons;
        public:
            TextButtonConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {}
            TextButtonConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            TextButton& build(const TextButton& textButton);
        };
    }
}


