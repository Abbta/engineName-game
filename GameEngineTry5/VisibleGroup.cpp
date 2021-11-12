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
	}
}