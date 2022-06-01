#include "RectangleConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a rectangle, put it and refs to it in correct storages
		Rectangle& RectangleConstructor::build(const Rectangle &rectangle)
		{
			//adds an empty spot in allvisibles, this signals that a new unique 
				//visible is constructed meaning it needs a unique layerID
			this->mf_makeRoomForNewVisible();
			//dynamically allocate a new rectangle
			this->mparr_allRectangles.push_back(std::make_unique<Rectangle>(rectangle));
			//add rectangle to allVisibles
			this->mf_registerNewVisible(*mparr_allRectangles.back());
			//return ref to newly constructed rectangle
			return *this->mparr_allRectangles.back();
		}

		//overload of above
		Rectangle& RectangleConstructor::build(Base::ObjectContainer& world,
			const Vector position, const td_width width, const td_height height, const Color color,
			const unsigned int borderWidth, const Color borderColor)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allRectangles.push_back(std::make_unique<Rectangle>(Rectangle(world, position, width, height, color, borderWidth, borderColor)));
			this->mf_registerNewVisible(*mparr_allRectangles.back());
			return *this->mparr_allRectangles.back();
		}
	}
}