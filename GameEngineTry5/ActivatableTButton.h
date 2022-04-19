#pragma once
#include "TextButton.h"
namespace EngineName
{
    namespace Object
    {
        /* ActivatableTextButton class
        *   Textbutton specialised to become activated and deactivated via task
        *   Contains two textRectangles, one for active mode and one for inactive
        *   Inactive mode also disables the OnClick for the button
        */
        class ActivatableTButton :
            public TextButton
        {
        protected:
            //Two textrectangles being the frames for active and inactive mode are stored in the class
            std::unique_ptr<TextRectangle> mpptr_activeTRect;
            std::unique_ptr<TextRectangle> mpptr_inactiveTRect;

            //Method that actually changes the Textrectangle part of class to the desired TR frame
            ActivatableTButton& mpf_changeTRBaseTo(const TextRectangle& textRectangle);
        public:
            //note how constructor is templated due to onClickTask being any task type
            template<class t_TaskType>
            ActivatableTButton(const TextRectangle& activeTRect, const TextRectangle& inactiveTRect, const t_TaskType& onClickTask, const bool isActive = false)
                : mpptr_activeTRect(std::make_unique<TextRectangle>(activeTRect)), mpptr_inactiveTRect(std::make_unique<TextRectangle>(inactiveTRect)),
                TextButton(inactiveTRect, onClickTask), Rectangle(inactiveTRect)
            {
                //toggle the OnClick
                mpc_actionRef.mp_toggle = isActive;
                //the toggle in OnClick is used to determine what mode ATButton is in
                if (mpc_actionRef.mp_toggle)
                    setActive();
            }

            //default constructor not templated
            ActivatableTButton(const ActivatableTButton& activatableTButton)
                :mpptr_activeTRect(std::make_unique<TextRectangle>(*activatableTButton.mpptr_activeTRect)),
                    mpptr_inactiveTRect(std::make_unique<TextRectangle>(*activatableTButton.mpptr_inactiveTRect)),
                    TextButton(activatableTButton), Rectangle(activatableTButton)
            {}

            //Methods for changing mode
            ActivatableTButton& setActive();
            ActivatableTButton& setInactive();
            ActivatableTButton& toggleActive();
        };

    }
}
