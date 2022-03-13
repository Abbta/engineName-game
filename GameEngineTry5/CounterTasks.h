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
			Object::Counter* mpptr_counter;

			virtual void mpf_perform(Base::ObjectContainer& world) override;
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

			Object::Display& mp_displayRef;
			Object::Counter* mpptr_counter;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				mp_displayRef.mp_updateDisplay(*mpptr_counter);
			}

		public:
			UpdateDisplay(Object::Display& display) :
				mp_displayRef(display), mpptr_counter(display.mptr_counter)
			{

			}

			void m_updateCounterPtr(Object::Counter& newCounter);
			friend class TaskContainer;
		};
	}
}