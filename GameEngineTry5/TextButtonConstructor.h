#pragma once
#include "ObjectConstructor.h"
#include "TextButton.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * textbuttonconstructor class
        * used for constructing textbuttons
        * has .build()
        *   constructs the object
        *   gives back ref
        * stores all textbuttons within itself
        */
        class TextButtonConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<TextButton>> mparr_allTextButtons;
        public:
            TextButtonConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            TextButton& build(const TextButton& textButton);
        };
    }
}


