#include "ButtonConstructor.h"
#include "Button.h"
namespace EngineName
{
	namespace Object
	{
		Button& ButtonConstructor::build(const Button& button)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allButtons.push_back(std::make_unique<Button>(button));
			this->mparr_allButtons.back()->mpf_changeOnClickArea(*mparr_allButtons.back());
			this->mf_registerNewVisible(*mparr_allButtons.back());
			return *this->mparr_allButtons.back();
		}
	}
}