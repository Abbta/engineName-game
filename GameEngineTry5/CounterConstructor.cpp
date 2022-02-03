#include "CounterConstructor.h"
namespace EngineName
{
	namespace Object
	{
        Counter<int, void>& CounterConstructor::build(const Counter<int, void>& counter)
        {
            mparr_intVoidCounters.push_back(std::make_unique<Counter<int, void>>(counter));
            return *mparr_intVoidCounters.back();
        }

        Counter<int, Time::UpdateDisplay<int>>& CounterConstructor::build(const Counter<int, Time::UpdateDisplay<int>>& counter)
        {
            mparr_intDisplayCounters.push_back(std::make_unique<Counter<int, Time::UpdateDisplay<int>>>(counter));
            return *mparr_intDisplayCounters.back();
        }
	}
}