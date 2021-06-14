#include "Rectangle.h"
#include "BrushContainer.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		//Draws the rectangle and/or the border if within a drawing context
		void Rectangle::mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const
		{
			renderTarget->FillRectangle(*this, (brushes.getBrush(renderTarget, color)));

			if (borderWidth > 0)
			{
				renderTarget->DrawRectangle(*this, brushes.getBrush(renderTarget, color), static_cast<FLOAT>(borderWidth));
			}
		}

		//requests drawing
		void Rectangle::draw() const
		{
			mptr_world->drawVisible(*this);
		}
	}
}