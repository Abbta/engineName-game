#include "Vector.h"
#include <math.h>
namespace EngineName
{
	namespace Object
	{
		Vector::operator bool() const
		{
			//TODO: make function check if coordinates is within the screen
			return x > 0 && y > 0 && x < 1000 && y < 1000;
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

		Vector::operator double() const
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		bool Vector::operator<(const Vector& vector) const
		{
			return static_cast<double>(*this) < static_cast<double>(vector);
		}

		Vector::operator D2D1_POINT_2F() const
		{
			return D2D1::Point2F(static_cast<FLOAT>(x), static_cast<FLOAT>(y));
		}
	}
}