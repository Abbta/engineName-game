#pragma once
#include "TextButton.h"
namespace EngineName
{
    namespace Object
    {
        class ActivatableTButton :
            public TextButton
        {
        protected:
            std::unique_ptr<TextRectangle> mpptr_activeTRect;
            std::unique_ptr<TextRectangle> mpptr_inactiveTRect;
            bool mp_isActive;

            ActivatableTButton& mpf_changeTRBaseTo(const TextRectangle& textRectangle);
        public:
            template<class t_TaskType>
            ActivatableTButton(const TextRectangle& activeTRect, const TextRectangle& inactiveTRect, const t_TaskType& onClickTask, const bool isActive = false)
                : mpptr_activeTRect(std::make_unique<TextRectangle>(activeTRect)), mpptr_inactiveTRect(std::make_unique<TextRectangle>(inactiveTRect)),
                TextButton(inactiveTRect, onClickTask)
            {
                if (isActive)
                    setActive();
            }

            ActivatableTButton& setActive();
            ActivatableTButton& setInactive();
            ActivatableTButton& toggleActive();
        };

    }
}
