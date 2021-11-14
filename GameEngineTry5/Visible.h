#include "Vector.h"
#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#include "PaintingOrder.h"
#include "Color.h"
#pragma once
#include "Object.h"

namespace EngineName
{
    namespace Base
    {
        class ObjectContainer;
    }
    namespace Drawing
    {
        class Painter;
        class BrushContainer;
    }
    namespace Object
    {
        /*
        * visible class
        * template class for all things that have a position and a shape
        * contains position elements
        * contains colour elements
        */
        class Visible :
            public Object
        {
        protected:
            virtual void mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const { throw; /*error cant draw pure visible*/ }
            void mpf_clear(CComPtr<ID2D1HwndRenderTarget>& renderTarget, CComPtr<ID2D1SolidColorBrush>& backgroundBrush) const;
            virtual bool mpf_isVisible() const override final { return true; }
        public:
            //has public and shortnamed members for easier dev access
            Visible(const Visible &v);
            Visible(Base::ObjectContainer& world,
                Vector position = Vector(0, 0), unsigned int width = 0, unsigned int height = 0, Color color = Color("000000FF"));
            //all visible have a box which is the smallest rect that contains the whole inner shape
            Vector boxPosition;
            unsigned int boxWidth;
            unsigned int boxHeight;
            Vector boxCenter;
            bool boxOverlaps(const Visible& visible) const; //returns if two visibles' boxes overlap
            bool boxContains(const Vector& point) const;
            
            virtual void translate(const Vector& translateVector); //changes position of visible

            PaintingOrder layerID; //is called ID to emphasize its need to be unique
            Color color;

            virtual void draw() const { throw; /*error cannot draw visible*/ } //dev can use this to tell a visible to draw itself

            bool operator==(const Visible& visible) const;
            bool operator!=(const Visible& visible) const { return !(*this == visible); }
            bool operator<(const Visible& visible) const;
            bool operator>(const Visible& visible) const { return !(*this < visible) && !(*this == visible); }
            bool operator<=(const Visible& visible) const { return !(*this > visible); }
            bool operator>=(const Visible& visible) const { return !(*this < visible); }
            operator D2D1_RECT_F() const;

            friend class Drawing::Painter;
        }; 
    }
}

