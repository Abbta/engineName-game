#include "DisplayConstructor.h"
namespace EngineName
{
	namespace Object
	{
		Display<int>& DisplayConstructor::build(const Display<int>& display)
		{
			this->mf_makeRoomForNewVisible();
			mparr_intDisplays.push_back(std::make_unique<Display<int>>(display));
			this->mf_registerNewVisible(*mparr_intDisplays.back());
			return *mparr_intDisplays.back();
		}
	}
}