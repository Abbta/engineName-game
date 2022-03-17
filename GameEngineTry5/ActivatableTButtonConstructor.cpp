#include "ActivatableTButtonConstructor.h"
#include "ActivatableTButton.h"
namespace EngineName
{
	namespace Object
	{
		ActivatableTButton& ActivatableTButtonConstructor::build(const ActivatableTButton& activatableTButton)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allATButtons.push_back(std::make_unique<ActivatableTButton>(activatableTButton));
			//register inactive part
			this->mf_registerNewVisible(*mparr_allATButtons.back()->mpptr_inactiveTRect);
			//also register active part, this means this visible will take up two spots in allVisibles and have two different layerIDs
			//essentially ActivatableTButton can be considered two visibles that are closely connected
			this->mf_makeRoomForNewVisible();
			this->mf_registerNewVisible(*mparr_allATButtons.back()->mpptr_activeTRect);

			return *this->mparr_allATButtons.back();
		}
	}
}