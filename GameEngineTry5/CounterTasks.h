#pragma once
#include "Task.h"
#include "Display.h"
#include "CounterImpl.h"
namespace EngineName
{
	namespace Time
	{
		class AddToCounter : public Task
		{
		protected:
			std::list<AddToCounter>* mptr_storageRef;
			std::list<AddToCounter>::iterator mpit_storageItRef;

			Object::Counter* mpptr_counter;

			virtual void mpf_perform(Base::ObjectContainer& world) override;

			virtual void Destroy() override
			{
				if (mp_isDestructable)
					mptr_storageRef->erase(mpit_storageItRef);
			}
		public:
			AddToCounter(Object::Counter& counter) :
				mpptr_counter(&counter)
			{

			}

			friend class TaskContainer;
		};


		class UpdateDisplay : public Task
		{
		private:
			std::list<UpdateDisplay>* mptr_storageRef;
			std::list<UpdateDisplay>::iterator mpit_storageItRef;

			Object::Display& mp_displayRef;
			Object::Counter* mpptr_counter;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				mp_displayRef.mp_updateDisplay(*mpptr_counter);
			}

			virtual void Destroy() override
			{
				if (mp_isDestructable)
					mptr_storageRef->erase(mpit_storageItRef);
			}
		public:
			UpdateDisplay(Object::Display& display) :
				mp_displayRef(display), mptr_storageRef(nullptr), mpptr_counter(display.mptr_counter)
			{

			}

			void m_updateCounterPtr(Object::Counter& newCounter);
			friend class TaskContainer;
		};
	}
}