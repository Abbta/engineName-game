#include "Button.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		Action::ActionListener& Button::msp_getActionListener(Base::ObjectContainer* worldPtr)
		{
			return worldPtr->mp_actionListener;
		}
	}
}