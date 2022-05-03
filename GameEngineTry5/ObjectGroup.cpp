#include "ObjectGroup.h"
namespace EngineName
{
	namespace Object
	{
		//add an object to group
		Object& ObjectGroup::add(Object& object)
		{
			mparr_objectPointers.push_back(&object);
			return *mparr_objectPointers.back();
		}
	}
}