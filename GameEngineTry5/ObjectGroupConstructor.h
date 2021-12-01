#pragma once
#include "ObjectGroup.h"
#include "ObjectConstructor.h"
namespace EngineName
{
	namespace Object
	{
		class ObjectGroupConstructor
			:public ObjectConstructor
		{
		private:
			std::list<std::unique_ptr<ObjectGroup>> mparr_allObjectGroups;
		public:
			ObjectGroupConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

			ObjectGroup& build(Base::ObjectContainer& world);
		};

	}
}

