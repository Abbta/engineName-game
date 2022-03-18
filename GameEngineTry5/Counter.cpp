#include "Counter.h"
namespace EngineName
{
	namespace Object
	{
		void Counter::mpf_increment(const void* amount)
		{
			throw Exceptions::BasicException("mpf_increment called from base class Counter");
		}
	}
}