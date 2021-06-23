#include "ActionListener.h"
#include "Vector.h"
#include "OnClick.h"
namespace EngineName
{
	namespace Action
	{
		void ActionListener::click(const unsigned int x, const unsigned int y)
		{
			Object::Vector point(x, y);
			std::list<std::unique_ptr<OnClick>>::iterator it;
			it = mparr_clickListeners.begin();
			while (it != mparr_clickListeners.end())
			{
				if ((*(*it)).onClick(x, y))
				{
					todo
				}
				it++;
			}
		}
	}
}