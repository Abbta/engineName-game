#include "DisplayConstructor.h"
namespace EngineName
{
	namespace Object
	{
		Display<int>& DisplayConstructor::build(const Display<int>& display)
		{
			mparr_intDisplays.push_back(std::make_unique<Display<int>>(display));
			return *mparr_intDisplays.back();
		}
	}
}