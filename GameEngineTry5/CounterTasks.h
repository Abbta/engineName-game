#pragma once
#include "Task.h"
#include "Display.h"
#include "CounterImpl.h"
namespace EngineName
{
	namespace Time
	{
		template<class t_CountType>
		class AddToCounter : public Task
		{
		protected:
			Object::Counter* mpptr_counter;
			t_CountType mp_amount;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				auto counterImpl = dynamic_cast<Object::CounterImpl<t_CountType, UpdateDisplay>*>(mpptr_counter);
				if (counterImpl == nullptr)
					throw Exceptions::BasicException("Type of AddToCounter doesn't match Counter");

				counterImpl += mp_amount;
			}
		public:
			AddToCounter(Object::Counter& counter, const t_CountType amount)) :
				mpptr_counter(&counter), mp_amount(amount)
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