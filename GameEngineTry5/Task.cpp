#include "Task.h"
namespace EngineName
{
	namespace Time
	{
		//adds an amunt of milliseconds to time left in queue, returns if time left in queue is positive
		bool Task::addTimeLeftInQueue(const std::chrono::milliseconds milliseconds)
		{
			mp_msLeftInQueue += milliseconds;
			return mp_msLeftInQueue.count() > 0;
		}

		//if task is destructable, removes it from container, i.e destroying it
		void Task::Destroy()
		{
			if(mp_isDestructable)
				mptr_storageRef->erase(mpit_storageItRef);
		}

		//Destroy that overrides is destructable variable
		void Task::mpf_destroyIndestructible()
		{
			mp_isDestructable = true;
			Destroy();
		}
	}
}