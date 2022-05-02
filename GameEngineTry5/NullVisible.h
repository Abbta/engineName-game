#pragma once
#include "Visible.h"
namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Object
    {
        /*
        * Nullvisible class
        * is only a placeholder that signals that there is no visible here
        * always has ID 0
        */
        class NullVisible :
            public Visible
        {
        protected:
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        public:
            NullVisible(Base::ObjectContainer* world): Visible(*world) {}
            virtual void draw() const override;

            virtual operator bool() const override { return false; }
        };
    }
}


