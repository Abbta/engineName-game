#pragma once
#include "Counter.h"
namespace EngineName
{
    namespace Object
    {
        template<class t_CountType, class t_TaskType>
        const t_CountType Counter<t_CountType, t_TaskType>::increment(const t_CountType& amount)
        {

        }

        template<class t_CountType, class t_TaskType>
        const t_CountType Counter<t_CountType, t_TaskType>::set(const t_CountType& newCount)
        {
            mp_count = newCount;
            if (mptr_onCountChange)
                mptr_world->mpc_theQueue.mpf_addToQueue(*mptr_onCountChange);
            return mp_count;
        }
    }
}