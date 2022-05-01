#include "CounterTasks.h"
namespace EngineName
{
	namespace Time
	{
		//assigns a new ref to mpptr_counter, used when constructing displayImpl
		void UpdateDisplay::m_updateCounterPtr(Object::Counter& newCounter)
		{
			mpptr_counter = &newCounter;
		}
	}
}