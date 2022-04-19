#include "CircleConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a rectangle, put it and refs to it in correct storages
		Circle& CircleConstructor::build(const Circle& circle)
		{
			//adds an empty spot in allvisibles, this signals that a new unique 
				//visible is constructed meaning it needs a unique layerID
			this->mf_makeRoomForNewVisible();
			//dynamically allocate a new circle
			this->mparr_allCircles.push_back(std::make_unique<Circle>(circle));
			//add circle to allVisibles
			this->mf_registerNewVisible(*mparr_allCircles.back());
			//return ref to newly constructed circle
			return *(this->mparr_allCircles.back());
		}

		//overload of above
		Circle& CircleConstructor::build(Base::ObjectContainer& world,
			const Vector& position, const td_radius radius, const Color& color)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allCircles.push_back(std::make_unique<Circle>(world, position, radius, color)); //dynamically allocate a new circle
			this->mf_registerNewVisible(*mparr_allCircles.back());
			return *(this->mparr_allCircles.back());
		}
	}
}