#include "PaintingOrder.h"
#include "Visible.h"
#include "ObjectContainer.h"

namespace EngineName
{
	namespace Object
	{
		//assumes last element in all visibles is where the owner of this painting order is to be placed
			//assigns painting order accordingly
		PaintingOrder::PaintingOrder(Base::ObjectContainer& world) : mptr_allVisible(&world.mparr_allVisibles) { mp_paintingOrder = mptr_allVisible->size() - 1; }

		//commented solution uses swapping ID with someone else instead of changing everyones ID
			//however it has not been decided if this is a practical solution
			//for now it is commented and Paintingorder does not support changing ID
		/*
		PaintingOrder& PaintingOrder::operator=(const unsigned int newPaintingOrder)
		{
			//because of unsigned we don't need to worry about below array range
			if (newPaintingOrder >= mptr_allVisible->size())
				//if dev entered a number greater than the array
			{
				//recursively make paintingorder the last 
				*this = static_cast<unsigned int>(mptr_allVisible->size() - 1);
			}
			else
			{
				//swap place in all-vector in order to end up att the correct place after paintingorder also swaps
				std::swap(mptr_allVisible->at(newPaintingOrder), mptr_allVisible->at(mp_paintingOrder));

				//switch paintingOrder with the object already having this paintingorder
				//this object is now on the spot where this object used to be, due to the swap above
				//this cannot be done recursively, would result in an infinite loop
				mptr_allVisible->at(this->mp_paintingOrder)->layerID.mp_paintingOrder = this->mp_paintingOrder;
				this->mp_paintingOrder = newPaintingOrder;
			}
			return *this;
		}
		*/
	}
}