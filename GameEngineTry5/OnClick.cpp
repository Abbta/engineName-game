#include "OnClick.h"
namespace EngineName
{
	namespace Action
	{
		bool OnClick::onClick(const unsigned int x, const unsigned int y)
		{
			if (mp_areaRef.boxContains(Object::Vector(x, y)))
			{
				mpf_schedule(mp_worldRef, mp_taskRef);
				return true;
			}
			return false;
		}
	}
}