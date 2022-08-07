#include "Vector.h"
#include <math.h>
#include "ObjectContainerAccess.h"
#include "WidthAndHeight.h"

//shorthands for width of world
#define world_width Base::ObjectContainerAccess::getWidth(world)
#define world_height Base::ObjectContainerAccess::getHeight(world)
namespace EngineName
{
	namespace Object
	{
		bool Vector::isOnScreen(Base::ObjectContainer& world) const
		{
			//TODO: make function check if coordinates is within the screen
			return x > 0 && y > 0 && x < world_width && y < world_height;
		}

		Vector Vector::operator+(const Vector& vector) const
		{
			Vector v(this->x + vector.x, this->y + vector.y);
			return v;
		}

		Vector Vector::operator-(const Vector& vector) const
		{
			Vector v(this->x - vector.x, this->y - vector.y);
			return v;
		}

		Vector& Vector::operator+=(const Vector& vector)
		{
			this->x += vector.x;
			this->y += vector.y;
			return *this;
		}

		bool Vector::operator==(const Vector& vector) const
		{
			return (this->x == vector.x) && (this->y == vector.y);
		}

		Vector::operator td_radius() const
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		bool Vector::operator<(const Vector& vector) const
		{
			return static_cast<td_radius>(*this) < static_cast<td_radius>(vector);
		}
	}
}