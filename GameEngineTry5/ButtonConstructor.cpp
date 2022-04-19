#include "ButtonConstructor.h"
#include "Button.h"
namespace EngineName
{
	namespace Object
	{
		//allocates memory, constructs and stores a button in world
		//returns ref to newly constructed
		Button& ButtonConstructor::build(const Button& button)
		{
			//adds an empty spot in allvisibles, this signals that a new unique 
				//visible is constructed meaning it needs a unique layerID
			this->mf_makeRoomForNewVisible();
			//construct the button dynamically
			this->mparr_allButtons.push_back(std::make_unique<Button>(button));
			//since on click area is a ref to button itself it needs to be assigned after button
				//has been constructed
			this->mparr_allButtons.back()->mpf_changeOnClickArea(*mparr_allButtons.back());
			//add button to allVisibles 
			this->mf_registerNewVisible(*mparr_allButtons.back());
			//return ref to button
			return *this->mparr_allButtons.back();
		}
	}
}