#include "Vector.h"
#include "Color.h"
#pragma once
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * line class
        * has origin point
        * has vector
        * from this, box is calculated
        */
        class Line :
            public Visible
        {
        public:
            Line(Base::ObjectContainer& world, const Vector& origin, const Vector& vector, const Color& color);

            Vector origin;
            Vector vector;
        };
    }
}

