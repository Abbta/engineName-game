#include "Circle.h"
#include "BrushContainer.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Object
	{
		//Constructor, also calculates box
		Circle::Circle(Base::ObjectContainer& world,
			const Vector& center, const td_radius radius, const Color& color)
			:Visible(world)
		{
			//error check radius
			if (radius < 0.0)
				throw Exceptions::BasicException("radius of circle can't be less than 0");

			//calculate box
			boxCenter = center;
			boxPosition = center - Vector(static_cast<td_xDirection>(radius), static_cast<td_yDirection>(radius)); //from center of circle go top left
			boxWidth = static_cast<td_width>(2 * radius);
			boxHeight = static_cast<td_height>(2 * radius);
			this->color = color;
			this->radius = radius;
		}

		//returns if a point lays within the circle
		bool Circle::contains(const Vector& point) const
		{
			//point - boxcenter is point going from boxcenter
			//magnitude of this vector <= radius
			return static_cast<double>(point - this->boxCenter) <= (this->radius);
		}

		//typecast to winapi D2D1 ellipse
		Circle::operator D2D1_ELLIPSE() const
		{
			return D2D1_ELLIPSE{D2D1::Point2F(mptr_world->width.toOutputWidth(boxCenter.x), mptr_world->height.toOutputHeight(boxCenter.y)),
				mptr_world->width.toOutputWidth(radius), mptr_world->width.toOutputWidth(radius) };
		}

		//performs the drawing if inside a drawing context
		void Circle::mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const
		{
			if (renderTarget == nullptr)
				throw Exceptions::BasicException("render target is null when drawing circle");

			renderTarget->FillEllipse(*this, brushes.getBrush(renderTarget, color));
		}

		//Requests drawing from painter
		void Circle::draw() const
		{
			this->mptr_world->drawVisible(*this);
		}
	}
}