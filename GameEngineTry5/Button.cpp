#include "Button.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		//builds button and adds action to the actionlistener
		Button::Button(const Rectangle& rect, const Action::OnClick& action)
			:Rectangle(rect), mp_actionRef(mptr_world->mp_actionListener.addClickListener(action))
		{
		}
	}
}