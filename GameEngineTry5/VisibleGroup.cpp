#include "VisibleGroup.h"
namespace EngineName
{
	namespace Object
	{
		Visible& VisibleGroup::add(Visible& visible)
		{
			mparr_visiblePointers.push_back(&visible);
			return *mparr_visiblePointers.back();
		}

		//get a visible from group via its id, lastindex param is used for optimization
		Visible& VisibleGroup::getFromID(const PaintingOrder& id, int& lastIndex)
		{
			//as the vector is sorted but with gaps, lastIndex parameter is used as optimization when iterating this function over several IDs
			//start with iterating from this indicator of where it is to be found
			for (int i(lastIndex); i < mparr_visiblePointers.size(); i++)
			{
				if (mparr_visiblePointers.at(i)->layerID == id)
				{
					lastIndex = i;
					return *mparr_visiblePointers.at(i);
				}
			}

			//if we get here no matching visible was found
			//try checking from start instead
			for (int i(0); i < mparr_visiblePointers.size(); i++)
			{
				if (mparr_visiblePointers.at(i)->layerID == id)
				{
					lastIndex = i;
					return *mparr_visiblePointers.at(i);
				}
			}

			//not found in the vector at all
			//error
			throw Exceptions::BasicException("No visible with the given ID was found in group\n");
		}

		//get if given visible is a part of group
		const bool VisibleGroup::contains(const Visible& visible) const
		{
			for (auto& element : mparr_visiblePointers)
			{
				if (visible == *element)
				{
					return true;
				}
			}
			return false;
		}
	}
}