#include "ActivatableTButton.h"
namespace EngineName
{
	namespace Object
	{
		ActivatableTButton& ActivatableTButton::mpf_changeTRBaseTo(const TextRectangle& textRectangle)
		{
			//change Visible components
			boxPosition = textRectangle.boxPosition;
			boxWidth = textRectangle.boxWidth;
			boxHeight = textRectangle.boxHeight;
			boxCenter = textRectangle.boxCenter;
			color = textRectangle.color;
			layerID = textRectangle.layerID;
				//constructor respnsible for making sure there's a placeholder visible on both layerID spots

			//change Rectangle components
			borderWidth = textRectangle.borderWidth;
			borderColor = textRectangle.borderColor;

			//change TextRectangle components
			mp_text = textRectangle.mp_text;
			mp_font = textRectangle.mp_font;
			mp_textColor = textRectangle.mp_textColor;
		}

		ActivatableTButton& ActivatableTButton::setActive()
		{
			mpf_changeTRBaseTo(*mpptr_activeTRect.get());
		}

		ActivatableTButton& ActivatableTButton::setInactive()
		{
			mpf_changeTRBaseTo(*mpptr_inactiveTRect.get());
		}

		ActivatableTButton& ActivatableTButton::toggleActive()
		{
			if (mp_isActive)
				setInactive();
			else
				setActive();
			return *this;
		}
	}
}