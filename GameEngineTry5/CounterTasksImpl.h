#pragma once
#include "CounterTasks.h"
namespace EngineName
{
	namespace Time
	{
		template<class t_CountType>
		class AddToCounterImpl : public AddToCounter
		{
		private:
			t_CountType mp_amount;

			virtual void mpf_perform(Base::ObjectContainer& world) override
			{
				auto counterImpl = dynamic_cast<Object::CounterImpl<t_CountType, UpdateDisplay>*>(mpptr_counter);
				if (counterImpl == nullptr)
					throw Exceptions::BasicException("Type of AddToCounter doesn't match Counter");

				counterImpl += mp_amount;
			}
		public:
			AddToCounterImpl(Object::Counter& counter, const t_CountType amount)
				: AddToCounter(counter), mp_amount(amount)
			{

			}
		};
	}
}