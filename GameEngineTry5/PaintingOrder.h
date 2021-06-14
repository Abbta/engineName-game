#include "BaseIncludeLibraries.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		class Visible;

		/*
		* paintingorder class
		* stores painting order
		*	in what order visibles are painted, also serves as indicator for where it is in an array
		*	is therefore unique for each visible
		* contains a static variable that keeps track of which next painting order that is to be handed out
		*/
		class PaintingOrder
		{
		private:
			unsigned int mp_paintingOrder; //is unsigned as it should correspond to an index of an array
			std::vector<Visible*>* mptr_allVisible; 
				//a ref to all other objects with this class, as to be able to change them when dev assigns new paintingorder
				//also works as a tracker for next paintingorder to assign to newly constructed objects
		public:
			PaintingOrder(Base::ObjectContainer& world);

			operator const int() const { return mp_paintingOrder; }
			PaintingOrder& operator=(const unsigned int newPaintingOrder); //Swaps paintingorder value with another paintingorder
			PaintingOrder& operator+=(const unsigned int addToPaintingOrder) { return *this = (*this + addToPaintingOrder); }
			PaintingOrder& operator++() { *this += 1;  }

		};
	}
}

