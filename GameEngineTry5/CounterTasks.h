#pragma once
#include "Task.h"
#include "Display.h"
#include "CounterImpl.h"
namespace EngineName
{
	namespace Time
	{
		/*
		* AddToCounter task
		* adds a specified amount to the specified counter
		* is template
		*/
		template<class t_CountType>
		class AddToCounter : public Task
		{
		protected:
			//pointer to counter which in reality is CounterImpl of t_CountType type
			Object::Counter* mpptr_counter;
			t_CountType mp_amount;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				//extract implemented part of mpptr_counter
				auto counterImpl = dynamic_cast<Object::CounterImpl<t_CountType, UpdateDisplay>*>(mpptr_counter);
				//note that the type of implemented part must match t_CountType in this class
				if (counterImpl == nullptr)
					throw Exceptions::BasicException("Type of AddToCounter doesn't match Counter");

				//perform the addition using overloaded operator
				*counterImpl += mp_amount;
			}
		public:
			AddToCounter(Object::Counter& counter, const t_CountType amount) :
				mpptr_counter(&counter), mp_amount(amount)
			{

			}

			friend class TaskContainer;
		};


		/*
		* Uppdate display task
		* updates the specified display to match the specified counter
		* used primarily by a counter associated with a display to 
		*	tell this display that count has been changed
		* why this is done via a task is mainly for consistensy
		*/
		class UpdateDisplay : public Task
		{
		private:

			Object::Display& mp_displayRef;
			//note that counter is actually counterImpl
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

			//assigns a new ref to mpptr_counter, used when constructing displayImpl
			void m_updateCounterPtr(Object::Counter& newCounter);
			friend class TaskContainer;
		};
	}
}