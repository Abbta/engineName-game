#include "Task.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Time
	{
		bool Task::addTimeLeftInQueue(const std::chrono::milliseconds milliseconds)
		{
			mp_msLeftInQueue += milliseconds;
			return mp_msLeftInQueue.count() > 0;
		}
	}
}