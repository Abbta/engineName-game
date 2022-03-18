#include "Button.h"
namespace EngineName
{
	namespace Object
	{
		void Button::mpf_changeOnClickArea(Visible& newArea)
		{
			mp_actionRef.mpf_changeArea(newArea);
		}
	}
}