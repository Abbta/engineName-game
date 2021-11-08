#include "ActionListener.h"
#include "Vector.h"
#include "OnClick.h"
namespace EngineName
{
	namespace Action
	{
		void ActionListener::click(const unsigned int x, const unsigned int y)
		{
			std::list<std::unique_ptr<OnClick>>::iterator it;
			it = mparr_clickListeners.begin();
			while (it != mparr_clickListeners.end())
			{
				if ((*(*it)).onClick(x, y))
				{
					//click was on button
					//only one button can be pressed
					//as they should be sorted from front to back visually
					//this is the only button that can be clicked
					//therefore function is terminated
					return;
				}
				it++;
			}
		}

		OnClick& ActionListener::addClickListener(const OnClick& listener)
		{
			
			std::list<std::unique_ptr<OnClick>>::const_iterator it;
			it = mparr_clickListeners.begin();
			while (it != mparr_clickListeners.end())
			{
				//if listener is visually in front of next element
				if (listener.mpptr_area > (*(*it)).mpptr_area)
				{
					//it should be inserted before that in the array
					return **mparr_clickListeners.insert(it, std::make_unique<OnClick>(listener));
					//returns ref to the newly inserted element
				}
				it++;
			}
			mparr_clickListeners.push_back(std::make_unique<OnClick>(listener));
			return *mparr_clickListeners.back();
		}
	}
}