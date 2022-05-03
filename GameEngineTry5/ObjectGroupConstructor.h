#pragma once
#include "ObjectGroup.h"
#include "ObjectConstructor.h"
namespace EngineName
{
	namespace Object
	{
		/*
		* Object group constructor class
		* constructs and stores objectgroups
		*/
		class ObjectGroupConstructor
			:public ObjectConstructor
		{
		private:
			//all objectgroups stored
			std::list<std::unique_ptr<ObjectGroup>> mparr_allObjectGroups;
		public:
			ObjectGroupConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

			ObjectGroup& build(Base::ObjectContainer& world);
		};

	}
}

