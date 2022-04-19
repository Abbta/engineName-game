#include "Button.h"
namespace EngineName
{
	namespace Object
	{
		/* Button::changeOnClickArea
		*	takes temporary visible as param
		*	changes area that actionRef checks on user clicks
		*/
		void Button::mpf_changeOnClickArea(const Visible& newArea)
		{
			mpc_actionRef.mpf_changeArea(newArea);
		}
	}
}