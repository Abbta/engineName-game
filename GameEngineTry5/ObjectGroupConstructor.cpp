#include "ObjectGroupConstructor.h"
namespace EngineName
{
	namespace Object
	{
		ObjectGroup& ObjectGroupConstructor::build(Base::ObjectContainer& world)
		{
			mparr_allObjectGroups.push_back(std::make_unique<ObjectGroup>(ObjectGroup(world)));
			return *mparr_allObjectGroups.back();
		}
	}
}