#include "Visible.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		Visible::Visible(const Visible& v)
			:Object(*v.mptr_world), 
			boxPosition(v.boxPosition), color(v.color), boxWidth(v.boxWidth), boxHeight(v.boxHeight), layerID(v.layerID)
		{
			boxCenter.x = v.boxCenter.x;
			boxCenter.y = v.boxCenter.y;
		}

		Visible::Visible(Base::ObjectContainer& world, Vector position, unsigned int width, unsigned int height, Color color)
			:Object(world), boxPosition(&position), color(color), boxWidth(width), boxHeight(height), layerID(world)
		{
			boxCenter.x = boxPosition.x + width / 2;
			boxCenter.y = boxPosition.y + height / 2;
		}

		//returns if two visibles' boxes overlap
		bool Visible::boxOverlaps(const Visible& visible) const
		{
			//if either of the visibles corners has coordinates that both is larger than boxPosition but smaller than boxPosition + width/height
			return ((visible.boxPosition.x > boxPosition.x
				&& visible.boxPosition.y > boxPosition.y
				&& visible.boxPosition.x < boxPosition.x + static_cast<int>(boxWidth)
				&& visible.boxPosition.y < boxPosition.y + static_cast<int>(boxHeight))
				|| (visible.boxPosition.x + static_cast<int>(visible.boxWidth) > boxPosition.x
					&& visible.boxPosition.y + static_cast<int>(visible.boxHeight) > boxPosition.y
					&& visible.boxPosition.x + visible.boxWidth < boxPosition.x + boxWidth
					&& visible.boxPosition.y + visible.boxHeight < boxPosition.y + boxHeight)
				//same but check for *this on visible instead
				|| (boxPosition.x > visible.boxPosition.x
					&& boxPosition.y > visible.boxPosition.y
					&& boxPosition.x < visible.boxPosition.x + static_cast<int>(visible.boxWidth)
					&& boxPosition.y < visible.boxPosition.y + static_cast<int>(visible.boxHeight))
				|| (boxPosition.x + static_cast<int>(boxWidth) > visible.boxPosition.x
					&& boxPosition.y + static_cast<int>(boxHeight) > visible.boxPosition.y
					&& boxPosition.x + boxWidth < visible.boxPosition.x + visible.boxWidth
					&& boxPosition.y + boxHeight < visible.boxPosition.y + visible.boxHeight));
		}

		void Visible::translate(const Vector& translateVector)
		{
			boxPosition += translateVector;
			boxCenter += translateVector;
		}

		bool Visible::operator==(const Visible& visible) const
		{
			return layerID == visible.layerID; //assumes layerID is unique
		}

		bool Visible::operator<(const Visible& visible) const
		{
			return layerID < visible.layerID;
		}

		Visible::operator D2D1_RECT_F() const
		{
			return D2D1::RectF(mptr_world->width.toOutputWidth(boxPosition.x), mptr_world->height.toOutputHeight(boxPosition.y),
				mptr_world->width.toOutputWidth(boxPosition.x + boxWidth), mptr_world->height.toOutputHeight(boxPosition.y + boxHeight));
		}

		void Visible::mpf_clear(CComPtr<ID2D1HwndRenderTarget>& renderTarget, CComPtr<ID2D1SolidColorBrush>& backgroundBrush) const
		{
			renderTarget->FillRectangle(*this, backgroundBrush);
		}
	}
}