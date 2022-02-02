#pragma once
//#include "OnClick.h"
#include "BaseIncludeLibraries.h"
namespace EngineName
{
	namespace Action
	{
		class OnClick;
		/*
		* ActionListener class
		* Keeps track of actions we're listening for, clicks and presses
		* When an action is spotted by the winapi it is sent to a function in ActionListener which checks
		* if any app objects are affected and perform these
		*/
		class ActionListener
		{
		private:
			std::list<std::unique_ptr<OnClick>> mparr_clickListeners;
		public:
			void click(const unsigned int x, const unsigned int y);

			OnClick& addClickListener(const OnClick& listener);
		};
	}
}
