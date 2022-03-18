#include "SceneConstructor.h"
namespace EngineName
{
	namespace Object
	{
		Scene& SceneConstructor::build(Base::ObjectContainer& world)
		{
			mparr_allScenes.push_back(std::make_unique<Scene>(Scene(world)));
			return *mparr_allScenes.back();
		}
	}
}