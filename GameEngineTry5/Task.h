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
	namespace Action
	{
		class OnActionBase;
		class OnClick;
	}
	namespace Time
	{
		class Queue;

		class Task
		{
		protected:
			//ptr to list where task is stored
			std::list<std::unique_ptr<Task>>* mptr_storageRef;
			//iteretor referensing position of task in storage container
			std::list<std::unique_ptr<Task>>::iterator mpit_storageItRef;
			//variable keeping track of time left in queue
			std::chrono::system_clock::duration mp_msLeftInQueue;

			//perform performs the task, child defines this function
			virtual void mpf_perform(Base::ObjectContainer& world) = 0;
			//tasks that are connected to for example buttons are set to be indestructible, sometimes (for example when
				//said button is destroyed) these need to be destroyed anyway
			void mpf_destroyIndestructible();
			//bool rendering the button unable to be destroyed via the Destroy() function
			bool mp_isDestructable;
		public:
			Task(): mp_msLeftInQueue(0), mp_isDestructable(true), mptr_storageRef(nullptr){}

			//makes button indestructible, meaning it will still remain after being executed, used for example in buttons
			void makeIndestructable() { mp_isDestructable = false; }

			//adds time until task execution, use negative integers for removing time, returns if mp_msLeftInQueue is positive
			bool addTimeLeftInQueue(const std::chrono::milliseconds milliseconds);

			//get time left
			std::chrono::system_clock::duration timeLeft() const { return mp_msLeftInQueue; }

			//destroys task 
			void Destroy();

			friend class Queue;
			friend class EngineName::Action::OnActionBase;
			friend class EngineName::Action::OnClick;
			friend class TaskContainer;
		};
	}
}