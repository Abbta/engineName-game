#pragma once
#include "ObjectConstructor.h"
#include "BaseIncludeLibraries.h"
#include "ActivatableTButton.h"
namespace EngineName
{
	namespace Object
	{
		/* ActivatableTextButtonConstructor class
		*	constructs and stores ATButtons
		*/
		class ActivatableTButtonConstructor:
			public ObjectConstructor
		{
		private:
			std::list<std::unique_ptr<ActivatableTButton>> mparr_allATButtons;

		public:
			ActivatableTButtonConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

			ActivatableTButton& build(const ActivatableTButton& button);
		};
	}
}

