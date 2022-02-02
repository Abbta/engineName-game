#pragma once
#include "ObjectTasks.h"
#include "Display.h"
namespace EngineName
{
	namespace Time
	{
		template<typename t_CountType>
		void UpdateDisplay<t_CountType>::mpf_perform(Base::ObjectContainer& world)
		{
			mp_displayRef.mp_updateDisplay(mp_counterRef);
		}

		template<typename t_CountType>
		void UpdateDisplay<t_CountType>::Destroy()
		{
			if (mp_isDestructable)
				mptr_storageRef->erase(mpit_storageItRef);
		}
	}
}