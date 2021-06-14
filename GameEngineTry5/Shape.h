#include "BaseIncludeLibraries.h"
#include "Vector.h"
#include "Color.h"
#pragma once
#include "Visible.h"
#define _Vector EngineName::Object::Vector //as just writing vector refers to EngineName::Object::Complex::Vector
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Object
    {
        namespace Complex
        {
            /*
            * Bezier class
            * Represents a n-dimensional Bezier
            * A Bezier is a way of representing a complex curve using 2 - 5 points
            *   2 points is just a normal straight line
            * Contains a vector with all the points
            * Contains values for the box surrounding the bezier
            */
            class Bezier
            {
            private:
                std::vector<_Vector> mparr_points;
                void mpf_initBox(std::vector<Vector>& points, Vector& position, unsigned int& height, unsigned int& width);
            public:
                Bezier(const _Vector& pointA, const _Vector& pointB, const _Vector& pointC = nullptr, const _Vector& pointD = nullptr, const _Vector& pointE = nullptr);
                Bezier(const std::vector<_Vector>& points);
                Bezier(const _Vector& originPoint, const int radius, const double rotationAngle);

                //has the same names as visible box-variables but it is not considered a visible
                    //optional TODO: make new class from which box is inherited
                _Vector boxPosition;
                unsigned int boxWidth; //is always positive
                unsigned int boxHeight; //always positive
            };

            /*
            * Shape class
            * Represents a more complex shape containing connected beziers
            * Contains a vector of beziers
            */
            class Shape :
                public Visible
            {
            private:
                std::vector<Bezier> mparr_outerLines;
            public:
                Shape(Base::ObjectContainer& world, Color& color, std::vector<Bezier>& outerLines);
            };
        }
    }
}
