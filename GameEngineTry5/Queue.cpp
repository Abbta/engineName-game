#include "Queue.h"
#include "Task.h"
namespace EngineName
{
	namespace Time
	{
		void Queue::mpf_addToQueue(Task& task)
		{
			//create task and store it at the correct place
			std::vector<Task*>::iterator it;
			it = mparr_theQueue.begin();
			do
			{
				if (it == mparr_theQueue.end())
				{
					mparr_theQueue.push_back(&task);
					break;
				}
				else if (task.timeLeft() > (*it)->timeLeft())
				{
					mparr_theQueue.insert(it, &task);
					break; //we know where to insert it, no further need to keep iterating
				}
				else
				{
					it++;
				}
			} while (it != mparr_theQueue.end());
		}

		/*
		* update function
		* member of queue
		* gets current time
		* uses queue to check how long it has been since last call
		* updates queue and adds to to-do list accordingly
		*/
		void Queue::mpf_update(Base::ObjectContainer& world)
		{
			if (mparr_theQueue.size() > 0)
			{
				std::vector<Task*> toDoList;
				const auto currentTime = std::chrono::system_clock::now();
				const auto timeSinceLastCall = std::chrono::duration_cast<std::chrono::milliseconds>(mp_timeAtLastCall - currentTime);
				mp_timeAtLastCall = currentTime;
				while (!mparr_theQueue.back()->addTimeLeftInQueue(timeSinceLastCall))
				{
					toDoList.push_back(mparr_theQueue.back());
					mparr_theQueue.pop_back();

					//break if queue empties
					if (mparr_theQueue.size() == 0)
						break;
				}

				std::vector<Task*>::const_iterator it;
				it = toDoList.begin();
				while(it != toDoList.end())
				{
					(*it)->mpf_perform(world);
					(*it)->Destroy();
					it = toDoList.erase(it);
				}
			}
		}
	}
}