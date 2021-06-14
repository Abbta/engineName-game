#include "CircleConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a rectangle, put it and refs to it in correct storages
		Circle& CircleConstructor::build(const Circle& circle)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allCircles.push_back(std::make_unique<Circle>(circle)); //dynamically allocate a new circle
			this->mf_registerNewVisible(*mparr_allCircles.back());
			return *(this->mparr_allCircles.back());
		}

		//overload of above
		Circle& CircleConstructor::build(Base::ObjectContainer& world,
			const Vector position, const int radius, const Color color)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allCircles.push_back(std::make_unique<Circle>(world, position, radius, color)); //dynamically allocate a new circle
			this->mf_registerNewVisible(*mparr_allCircles.back());
			return *(this->mparr_allCircles.back());
		}
	}
}