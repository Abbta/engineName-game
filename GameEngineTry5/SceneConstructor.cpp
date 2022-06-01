#include "SceneConstructor.h"
namespace EngineName
{
	namespace Object
	{
		//builds a new empty scene
		Scene& SceneConstructor::build(Base::ObjectContainer& world)
		{
			//construct dynamically and store
			mparr_allScenes.push_back(std::make_unique<Scene>(Scene(world)));
			return *mparr_allScenes.back();
		}
	}
}