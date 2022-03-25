#include "ActivatableTButton.h"
namespace EngineName
{
	namespace Object
	{
		/* ATButton::changeTextRectangleBaseTo()
		*	changes TextRectangle part of class
		*	takes temporary TextRectangle as param
		*	returns *this
		*/
		ActivatableTButton& ActivatableTButton::mpf_changeTRBaseTo(const TextRectangle& textRectangle)
		{
			//change Visible components
			boxPosition = textRectangle.boxPosition;
			boxWidth = textRectangle.boxWidth;
			boxHeight = textRectangle.boxHeight;
			boxCenter = textRectangle.boxCenter;
			color = textRectangle.color;
			//layer ID is static for whole object

			//change Rectangle components
			borderWidth = textRectangle.borderWidth;
			borderColor = textRectangle.borderColor;

			//change TextRectangle components
			mp_text = textRectangle.mp_text;
			mp_font = textRectangle.mp_font;
			mp_textColor = textRectangle.mp_textColor;
			return *this;
		}

		//sets mode to active
		ActivatableTButton& ActivatableTButton::setActive()
		{
			mpf_changeTRBaseTo(*mpptr_activeTRect.get());
			//mp_toggle in actionRef is used to determine what mode class is in
			mp_actionRef.mp_toggle = true;
			//make it check for correct area in clicklistener
			mpf_changeOnClickArea(*mpptr_activeTRect);
			return *this;
		}

		//sets mode to inactive
		ActivatableTButton& ActivatableTButton::setInactive()
		{
			mpf_changeTRBaseTo(*mpptr_inactiveTRect.get());
			//mp_toggle in actionRef is used to determine what mode class is in
			mp_actionRef.mp_toggle = false;
			//make it check for correct area in clicklistener
			mpf_changeOnClickArea(*mpptr_inactiveTRect);
			return *this;
		}

		//sets mode to whatever it is not at the moment
		ActivatableTButton& ActivatableTButton::toggleActive()
		{
			if (mp_actionRef.mp_toggle)
				setInactive();
			else
				setActive();
			return *this;
		}
	}
}