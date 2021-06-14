#include "RectangleConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a rectangle, put it and refs to it in correct storages
		Rectangle& RectangleConstructor::build(const Rectangle &rectangle)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allRectangles.push_back(std::make_unique<Rectangle>(rectangle));
			this->mf_registerNewVisible(*mparr_allRectangles.back());
			return *this->mparr_allRectangles.back();
		}

		//overload of above
		Rectangle& RectangleConstructor::build(Base::ObjectContainer& world,
			const Vector position, const int width, const int height, const Color color,
			const unsigned int borderWidth, const Color borderColor)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allRectangles.push_back(std::make_unique<Rectangle>(Rectangle(world, position, width, height, color, borderWidth, borderColor)));
			this->mf_registerNewVisible(*mparr_allRectangles.back());
			return *this->mparr_allRectangles.back();
		}
	}
}