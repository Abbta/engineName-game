#include "GraphicsIncludeLibraries.h"
#pragma once
#define Point Vector //the same class can be used to represent a point and a vector
namespace EngineName
{
	namespace Object
	{
		/*
		* Vector class
		* Contains position elements (x, y)
		* Also contains operators for these
		* This class can also be used under the name Point
		*/
		class Vector
		{
		public:
			Vector() : x(0), y(0) {}
			Vector(const int x, const int y) : x(x), y(y) {}
			Vector(const double x, const double y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}
			Vector(const double x, const int y) : x(static_cast<int>(x)), y(y) {}
			Vector(const int x, const double y) : x(x), y(static_cast<int>(y)) {}
			Vector(Vector& v) : x(v.x), y(v.y) {}
			Vector(Vector* v) : x(v->x), y(v->y) {}
			Vector(const Vector& v) : x(v.x), y(v.y) {}
			Vector(const unsigned int x, const unsigned int y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}
			//these variables does not follow naming convention due to easier access
			int x;
			int y;

			//operators, vector operations
			//vector addition
			Vector operator+(const Vector& vector) const;
			//difference between vectors
			Vector operator-(const Vector& vector) const;
			//change position via vector addition
			Vector& operator+=(const Vector& vector);
			//get the magnitude of the vector
			operator double() const;

			//boolean operators
			//compare two positions
			bool operator==(const Vector& vector) const;
			bool operator!=(const Vector& vector) const { return !(*this == vector); }
			//compare the magnitude of two vectors
			bool operator<(const Vector& vector) const;
			bool operator>=(const Vector& vector) const { return !(*this < vector); }
			//get if position is on the screen
			operator bool() const;

		};
	}
}