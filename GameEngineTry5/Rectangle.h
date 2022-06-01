#pragma once
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * rectangle class
        * has the same box as parent
        * has border width elemnt
        * has border color
        */
        class Rectangle :
            public Visible
        {
        protected:
            //draws itself if within a drawing context
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        public:
            //public members with short names for easier dev access
            Rectangle(const Rectangle& r):
                Visible(*r.mptr_world, r.boxPosition, r.boxWidth, r.boxHeight, r.color), borderWidth(r.borderWidth), borderColor(r.borderColor) {}
            Rectangle(Base::ObjectContainer& world, 
                const Vector& position = Vector(0, 0), const td_width width = 0, const td_height height = 0, const Color& color = Color("000000"),
                const td_width borderWidth = 0, const Color& borderColor = Color("00000000"))
                :Visible(world, position, width, height, color), borderWidth(borderWidth), borderColor(borderColor) {}
            Rectangle(Base::ObjectContainer& world,
                const Vector& position = Vector(0, 0), const double width = 0.0, const double height = 0.0, const Color& color = Color("000000"),
                const td_width borderWidth = 0, const Color& borderColor = Color("00000000"))
                :Visible(world, position, static_cast<td_width>(width), static_cast<td_height>(height), color), borderWidth(borderWidth), borderColor(borderColor) {}
                
            //requests drawing of itself
            void draw() const override;

            td_width borderWidth;
            Color borderColor;
        };
    }
}

