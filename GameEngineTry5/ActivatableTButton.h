#pragma once
#include "TextButton.h"
namespace EngineName
{
    namespace Object
    {
        class ActivatableTButtonConstructor;
        class ActivatableTButton :
            public TextButton
        {
        protected:
            std::unique_ptr<TextRectangle> mpptr_activeTRect;
            std::unique_ptr<TextRectangle> mpptr_inactiveTRect;

            ActivatableTButton& mpf_changeTRBaseTo(const TextRectangle& textRectangle);
        public:
            template<class t_TaskType>
            ActivatableTButton(const TextRectangle& activeTRect, const TextRectangle& inactiveTRect, const t_TaskType& onClickTask, const bool isActive = false)
                : mpptr_activeTRect(std::make_unique<TextRectangle>(activeTRect)), mpptr_inactiveTRect(std::make_unique<TextRectangle>(inactiveTRect)),
                TextButton(inactiveTRect, onClickTask), Rectangle(inactiveTRect)
            {
                mp_actionRef.mp_toggle = isActive;
                if (mp_actionRef.mp_toggle)
                    setActive();
            }

            ActivatableTButton(const ActivatableTButton& activatableTButton)
                :mpptr_activeTRect(std::make_unique<TextRectangle>(*activatableTButton.mpptr_activeTRect)),
                    mpptr_inactiveTRect(std::make_unique<TextRectangle>(*activatableTButton.mpptr_inactiveTRect)),
                    TextButton(activatableTButton), Rectangle(activatableTButton)
            {}

            ActivatableTButton& setActive();
            ActivatableTButton& setInactive();
            ActivatableTButton& toggleActive();
            friend class ActivatableTButtonConstructor;
        };

    }
}
