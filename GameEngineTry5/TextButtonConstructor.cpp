#include "TextButtonConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//allocates memory, constructs and stores a button in world
		//returns ref to newly constructed
		TextButton& TextButtonConstructor::build(const TextButton& textButton)
		{
			//adds an empty spot in allvisibles, this signals that a new unique 
				//visible is constructed meaning it needs a unique layerID
			this->mf_makeRoomForNewVisible();
			//construct the button dynamically
			this->mparr_allTextButtons.push_back(std::make_unique<TextButton>(textButton));
			//since on click area is a ref to button itself it needs to be assigned after button
				//has been constructed
			this->mparr_allTextButtons.back()->mpf_changeOnClickArea(*mparr_allTextButtons.back());
			//add button to allVisibles 
			this->mf_registerNewVisible(*mparr_allTextButtons.back());
			//return ref to button
			return *this->mparr_allTextButtons.back();
		}
	}
}