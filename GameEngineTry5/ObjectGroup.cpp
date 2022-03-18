#include "ObjectGroup.h"
namespace EngineName
{
	namespace Object
	{
		Object& ObjectGroup::add(Object& object)
		{
			mparr_objectPointers.push_back(&object);
			return *mparr_objectPointers.back();
		}
	}
}