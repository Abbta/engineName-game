#include "Line.h"
namespace EngineName
{
	namespace Object
	{
		Line::Line(Base::ObjectContainer& world, const Vector& origin, const Vector& vector, const Color& color)
			:Visible(world, origin, vector.x, vector.y, color), origin(origin), vector(vector)
		{
		}
	}
}