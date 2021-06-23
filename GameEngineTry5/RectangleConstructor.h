#include "Rectangle.h"
#pragma once
#include "ObjectConstructor.h"
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Object
    {
        /*
        * rectangleconstructor class
        * used for constructing rectangles
        * has .build()
        *   constructs the object
        *   gives back ref
        * stores all rectangles within itself
        */
        class RectangleConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Rectangle>> mparr_allRectangles; //stores all dev constructed rectangles
        public:
            RectangleConstructor(Base::ObjectContainer &world): ObjectConstructor(world) {}
            RectangleConstructor(Base::ObjectContainer* world): ObjectConstructor(world) {}

            Rectangle& build(const Rectangle &rectangle);
            Rectangle& build(Base::ObjectContainer& world,
                const Vector position = &Vector(0, 0), const int width = 0, const int height = 0, const Color color = Color("000000"),
                const unsigned int borderWidth = 0, const Color borderColor = Color("00000000")); //creates a rectangle
            Rectangle& build(Base::ObjectContainer& world,
                const Vector position = &Vector(0, 0), const double width = 0, const double height = 0, const Color color = Color("000000"),
                const unsigned int borderWidth = 0, const Color borderColor = Color("00000000"))
            {
                return build(world, position, static_cast<const int>(width), static_cast<const int>(height), color, borderWidth, borderColor);
            }
        };
    }
}

