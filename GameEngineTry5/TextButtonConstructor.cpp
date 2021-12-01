#include "TextButtonConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//construct a Button, put it and refs to it in correct storages
		TextButton& TextButtonConstructor::build(const TextButton& textButton)
		{
			this->mf_makeRoomForNewVisible();
			this->mparr_allTextButtons.push_back(std::make_unique<TextButton>(textButton));
			this->mparr_allTextButtons.back()->mpf_changeOnClickArea(*mparr_allTextButtons.back());
			this->mf_registerNewVisible(*mparr_allTextButtons.back());
			return *this->mparr_allTextButtons.back();
		}
	}
}