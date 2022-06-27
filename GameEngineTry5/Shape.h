#include "BaseIncludeLibraries.h"
#include "Vector.h"
#include "Color.h"
#pragma once
#include "Visible.h"

////Shape is under development
//namespace EngineName
//{
//    namespace Base
//    {
//        class ObjectContainer;
//    }
//    namespace Object
//    {
//        namespace Complex
//        {
//            /*
//            * Bezier class
//            * Represents a n-dimensional Bezier
//            * A Bezier is a way of representing a complex curve using 2 - 5 points
//            *   2 points is just a normal straight line
//            * Contains a vector with all the points
//            * Contains values for the box surrounding the bezier
//            */
//            class Bezier
//            {
//            private:
//                std::vector<Vector> mparr_points;
//                void mpf_initBox(std::vector<Vector>& points, Vector& position, td_height& height, td_width& width);
//            public:
//                Bezier(const Vector& pointA, const Vector& pointB, const Vector& pointC = nullptr, const Vector& pointD = nullptr, const Vector& pointE = nullptr);
//                Bezier(const std::vector<Vector>& points);
//                Bezier(const Vector& originPoint, const td_radius radius, const td_angle rotationAngle);
//
//                //has the same names as visible box-variables but it is not considered a visible
//                    //optional TODO: make new class from which box is inherited
//                Vector boxPosition;
//                unsigned int boxWidth; //is always positive
//                unsigned int boxHeight; //always positive
//            };
//
//            /*
//            * Shape class
//            * Represents a more complex shape containing connected beziers
//            * Contains a vector of beziers representing the outer lines of the shape
//            */
//            class Shape :
//                public Visible
//            {
//            private:
//                //TODO: method for drawing itself
//                std::vector<Bezier> mparr_outerLines;
//            public:
//                Shape(Base::ObjectContainer& world, Color& color, std::vector<Bezier>& outerLines);
//            };
//        }
//    }
//}
//
