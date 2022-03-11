#include "CounterTasks.h"
namespace EngineName
{
	namespace Time
	{
		void AddToCounter::mpf_perform(Base::ObjectContainer& world)
		{
			throw Exceptions::BasicException("AddToCounter called from base class instead of implemented class");
		}

		void UpdateDisplay::m_updateCounterPtr(Object::Counter& newCounter)
		{
			mpptr_counter = &newCounter;
		}
	}
}