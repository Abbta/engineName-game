#include "CounterTasks.h"
namespace EngineName
{
	namespace Time
	{
		void UpdateDisplay::m_updateCounterPtr(Object::Counter& newCounter)
		{
			mpptr_counter = &newCounter;
		}
	}
}