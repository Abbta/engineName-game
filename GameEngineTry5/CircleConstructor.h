#include "BaseIncludeLibraries.h"
#include "Circle.h"
#pragma once
#include "ObjectConstructor.h"
namespace EngineName
{
    namespace Object
    {
        /*
       * Circle constructor class
       * Used for constructing circles
       * Has .build()
       *   constructs the object
       *   gives back ref
       * Stores all circles within itself
       */
        class CircleConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Circle>> mparr_allCircles; //stores all dev constructed circles
        public:
            CircleConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {}

            Circle& build(const Circle& circle);
            Circle& build(Base::ObjectContainer& world,
                const Vector& position = &Vector(0, 0), const td_radius radius = 0.0, const Color& color = Color("000000"));

            friend class Drawing::Painter;
        };
    }
}

