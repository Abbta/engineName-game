#include "Display.h"
#include "ObjectContainer.h"
#include "ObjectTasks.h"
namespace EngineName
{
	namespace Object
	{
		template<typename t_CountType>
		Counter<t_CountType, Time::UpdateDisplay<t_CountType>> inlinef_buildCounter(Base::ObjectContainer *world, Display<t_CountType>* thisPtr, const t_CountType initialCount = 0)
		{
			auto tempTaskPtr = &Time::UpdateDisplay<t_CountType>(*thisPtr);
			return world->counter.build(Counter<t_CountType, Time::UpdateDisplay<t_CountType>>(*world, initialCount, tempTaskPtr));
		}

	}
}