#include "Visible.h"
#include "ObjectContainerAccess.h"
#include "WidthAndHeight.h"

//shorthands for width of world
#define world_width Base::ObjectContainerAccess::getWidth(*mptr_world)
#define world_height Base::ObjectContainerAccess::getHeight(*mptr_world)
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

		Visible::Visible(Base::ObjectContainer& world, Vector position, td_width width, td_height height, Color color)
			:Object(world), boxPosition(&position), color(color), boxWidth(width), boxHeight(height), layerID(world)
		{
			boxCenter.x = boxPosition.x + width / 2;
			boxCenter.y = boxPosition.y + height / 2;
		}

		//returns if two visibles' boxes overlap
		bool Visible::boxOverlaps(const Visible& visible) const
		{
			//check if both visibles are in the active scene
			auto activeScene = Base::ObjectContainerAccess::getActiveScene(*mptr_world);
			if(activeScene)
				if (!(activeScene->contains(visible) && activeScene->contains(*this)))
					return false;

			//if either of the visibles corners has coordinates that both is larger than boxPosition but smaller than boxPosition + width/height
			return ((visible.boxPosition.x > boxPosition.x
				&& visible.boxPosition.y > boxPosition.y
				&& visible.boxPosition.x < boxPosition.x + static_cast<td_width>(boxWidth)
				&& visible.boxPosition.y < boxPosition.y + static_cast<td_height>(boxHeight))
				|| (visible.boxPosition.x + static_cast<td_width>(visible.boxWidth) > boxPosition.x
					&& visible.boxPosition.y + static_cast<td_height>(visible.boxHeight) > boxPosition.y
					&& visible.boxPosition.x + visible.boxWidth < boxPosition.x + boxWidth
					&& visible.boxPosition.y + visible.boxHeight < boxPosition.y + boxHeight)
				//same but check for *this on visible instead
				|| (boxPosition.x > visible.boxPosition.x
					&& boxPosition.y > visible.boxPosition.y
					&& boxPosition.x < visible.boxPosition.x + static_cast<td_width>(visible.boxWidth)
					&& boxPosition.y < visible.boxPosition.y + static_cast<td_height>(visible.boxHeight))
				|| (boxPosition.x + static_cast<td_width>(boxWidth) > visible.boxPosition.x
					&& boxPosition.y + static_cast<td_height>(boxHeight) > visible.boxPosition.y
					&& boxPosition.x + boxWidth < visible.boxPosition.x + visible.boxWidth
					&& boxPosition.y + boxHeight < visible.boxPosition.y + visible.boxHeight));
		}

		//check if a point is within the box
		bool Visible::boxContains(const Vector& point) const
		{
			return point.x > boxPosition.x && point.y > boxPosition.y
				&& point.x < static_cast<td_width>(boxPosition.x + boxWidth) && point.y < static_cast<td_height>(boxPosition.y + boxHeight);
		}

		//translate (move) the visible
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
			return D2D1::RectF(world_width.toOutputWidth(boxPosition.x), world_height.toOutputHeight(boxPosition.y),
				world_width.toOutputWidth(boxPosition.x + boxWidth), world_height.toOutputHeight(boxPosition.y + boxHeight));
		}

		void Visible::mpf_clear(CComPtr<ID2D1HwndRenderTarget>& renderTarget, CComPtr<ID2D1SolidColorBrush>& backgroundBrush) const
		{
			renderTarget->FillRectangle(*this, backgroundBrush);
		}
	}
}