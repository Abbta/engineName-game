#pragma once
#include "Visible.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * Circle class
        * Has center
        * Has radius
        * Box is calculated from this
        * 
        * Has draw function which draws the circle if inside a drawing context
        * Has contains functions which returns if a point lays within the circle
        */
        class Circle :
            public Visible
        {
        protected:
            //performs the actual drawing when inside drawing context
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const override;
        public:
            Circle(const Circle& c) :
                Circle(*c.mptr_world, c.boxCenter, c.radius, c.color) {}
            Circle(Base::ObjectContainer& world,
                const Vector& center = &Vector(0, 0), const td_radius radius = 0.0, const Color& color = Color("00000000"));
            
            td_radius radius;

            //Draws circle, must be called inside beginDraw()
            virtual void draw() const override;

            //temporary name, returns if a point lays within the circle
            bool contains(const Vector& point) const;

            //returns circle as the drawable winapi object
            operator D2D1_ELLIPSE() const;
        };
    }
}

