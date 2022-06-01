#include "Queue.h"
#include "Task.h"
namespace EngineName
{
	namespace Time
	{
		//adds a task to the queue, sorted by how much time there is left, least time at back
		void Queue::mpf_addToQueue(Task& task)
		{
			//create task and store it at the correct place
			std::vector<Task*>::iterator it;
			it = mparr_theQueue.begin();
			do
			{
				//if the end is reached
				if (it == mparr_theQueue.end())
				{
					//add task to back
					mparr_theQueue.push_back(&task);
					break;
				}
				//if we have iterated past the last element that has more time left than task
				else if (task.timeLeft() > (*it)->timeLeft())
				{
					//insert task there
					mparr_theQueue.insert(it, &task);
					break; //we know where to insert it, no further need to keep iterating
				}
				else
				{
					//else keep iterating
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
			//if there is a queue
			if (mparr_theQueue.size() > 0)
			{
				//to do list is a vector of all tasks that will be scheduled this update
				std::vector<Task*> toDoList;

				//keep track of time
				const auto currentTime = std::chrono::system_clock::now();
				const auto timeSinceLastCall = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - mp_timeAtLastCall);
				mp_timeAtLastCall = currentTime;

				//from the back of queue, check if element has negative time left
					//when we have removed time since last call. If it has then remove it and 
					//schedule it.  Break when an element still has time left or queue empties
				while (!mparr_theQueue.back()->addTimeLeftInQueue(-timeSinceLastCall))
				{
					toDoList.push_back(mparr_theQueue.back());
					mparr_theQueue.pop_back();

					//break if queue empties
					if (mparr_theQueue.size() == 0)
						break;
				}

				//if there still are elements left in the queue, except for the one that broke that last loop
					//remove time from them aswell, we can assume all of them end up with positive time since queue is sorted
				if(mparr_theQueue.size() > 0)
					//if statement needed as .size() will return an unsigned integer and - 1 on 0 will overflow
					for (int i(0); i < mparr_theQueue.size() - 1; i++)
					{
						//note that the last element in queue is not uppdated since it was already updated in the last loop
						mparr_theQueue[i]->addTimeLeftInQueue(-timeSinceLastCall);
					}

				//schedule all tasks that has been added to the to do list and remove them from it
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