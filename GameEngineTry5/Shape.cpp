#include "Shape.h"
namespace EngineName
{
    namespace Object
    {
        namespace Complex
        {
            //Constructor, also calculates box
            Shape::Shape(Base::ObjectContainer& world, Color& color, std::vector<Bezier>& outerLines)
                :Visible(world), mparr_outerLines(outerLines)
            {
                if (outerLines.size() > 0)
                {
                    //Initialise comparison values with "worst" possible
                    int lowX = 0x11111111;
                    int lowY = 0x11111111;
                    unsigned int highX = 0;
                    unsigned int highY = 0;
                    
                    //iterate through all points and see if any of them are outside of the comparison box
                    for (int i(0); i < mparr_outerLines.size(); i++)
                    {
                        lowX = mparr_outerLines[i].boxPosition.x < lowX ?
                            mparr_outerLines[i].boxPosition.x : lowX;
                        lowY = mparr_outerLines[i].boxPosition.y < lowY ?
                            mparr_outerLines[i].boxPosition.y: lowY;
                        highX = mparr_outerLines[i].boxPosition.x + mparr_outerLines[i].boxWidth > highX ?
                            mparr_outerLines[i].boxPosition.x + mparr_outerLines[i].boxWidth: highX;
                        highY = mparr_outerLines[i].boxPosition.y + mparr_outerLines[i].boxHeight > highY ?
                            mparr_outerLines[i].boxPosition.y + mparr_outerLines[i].boxHeight: highY;
                       
                    }

                    //initialise the box 
                    boxPosition = Vector(lowX, lowY);
                    boxWidth = highX - lowX;
                    boxHeight = highY - lowY;
                    boxCenter.x = boxPosition.x + boxWidth / 2;
                    boxCenter.y = boxPosition.y + boxHeight / 2;
                }
            }

            //Constructor, also initializes box
            Bezier::Bezier(const Vector& pointA, const Vector& pointB, const Vector& pointC, const Vector& pointD, const Vector& pointE)
            {
                //initialise the paramteres if they are not null
                if (pointA != nullptr)
                    mparr_points.push_back(pointA);
                else
                    throw Exceptions::BasicException("Error: first point of Bezier can't be null");
                if (pointB != nullptr)
                    mparr_points.push_back(pointB);
                else
                    throw Exceptions::BasicException("Error: second point of Bezier can't be null");
                if (pointC != nullptr)
                    mparr_points.push_back(pointC);
                //does not need to throw as Bezier does not need more than 2 points to function
                if (pointD != nullptr)
                    mparr_points.push_back(pointD);
                if (pointE != nullptr)
                    mparr_points.push_back(pointE);

                mpf_initBox(mparr_points, boxPosition, boxHeight, boxWidth);
            }

            //overload of the above
            Bezier::Bezier(const std::vector<Vector>& points)
            {
                if (points.size() >= 2 && points.size() <= 5)
                {
                    for (int i(0); i < points.size(); i++)
                    {
                        if (points[i] != nullptr)
                        {
                            mparr_points.push_back(points[i]);
                        }
                        else
                            throw Exceptions::BasicVariableException<int>("point $ in initialier list for Bezier is null", i);
                    }
                }
                else
                    throw Exceptions::BasicVariableException<size_t>("size of list initializing points in Bezier is $, min is 2, max is 5", points.size());
                mpf_initBox(mparr_points, boxPosition, boxHeight, boxWidth);
            }

            /*
            Bezier::Bezier(const Vector& originPoint, const int radius, const double rotationAngle)
            {
                //TODO:
                //make a function that translates arcs to Beziers
            }*/

            //calculates an aproximate box to to bezier
            void Bezier::mpf_initBox(std::vector<Vector>& points, Vector &position, unsigned int &height, unsigned int& width)
            {
                position = Vector(0xFFFFFFF, 0xFFFFFFF);
                int highestY = 0;
                int highestX = 0;
                for (int i(0); i < points.size(); i++)
                {
                    if (points[i] < position)
                        position = points[i];
                    highestY == points[i].y > highestY ? points[i].y : highestY;
                    highestX == points[i].x > highestX ? points[i].x : highestX;
                }
            }

        }
    }
}