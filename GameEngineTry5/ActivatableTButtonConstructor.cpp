#include "ActivatableTButtonConstructor.h"
#include "ActivatableTButton.h"
namespace EngineName
{
	namespace Object
	{
		ActivatableTButton& ActivatableTButtonConstructor::build(const ActivatableTButton& activatableTButton)
		{
			this->mf_makeRoomForNewVisible();
			//all visibles within share the same layerID
			this->mparr_allATButtons.push_back(std::make_unique<ActivatableTButton>(activatableTButton));
			this->mparr_allATButtons.back()->setActive();
			this->mf_registerNewVisible(*mparr_allATButtons.back());

			return *this->mparr_allATButtons.back();
		}
	}
}