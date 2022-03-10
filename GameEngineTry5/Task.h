#include "BaseIncludeLibraries.h"
#pragma once
/*
* Task class
* base for tasks
* has schedule() function which puts the task in the queue
* has perform() function which executes the task
* has member variable which keep track of time left in queue
*/
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Time
	{
		class Queue;

		class Task
		{
		protected:
			std::list<std::unique_ptr<Task>>* mptr_storageRef;
			std::list<std::unique_ptr<Task>>::iterator mpit_storageItRef;
			std::chrono::system_clock::duration mp_msLeftInQueue;

			//the actual task
			virtual void mpf_perform(Base::ObjectContainer& world) = 0;
			void Destroy();
		public:
			Task(): mp_msLeftInQueue(0), mptr_storageRef(nullptr) {}

			//reschedules task execution, use negative integers for removing time, returns if mp_msLeftInQueue is positive
			bool addTimeLeftInQueue(const std::chrono::milliseconds milliseconds);

			//get time left
			std::chrono::system_clock::duration timeLeft() const { return mp_msLeftInQueue; }

			friend class Queue;
		};
	}
}