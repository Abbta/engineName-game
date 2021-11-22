#pragma once
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        class NullVisible :
            public Visible
        {
        protected:
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        public:
            virtual void draw() const override;
        };
    }
}


