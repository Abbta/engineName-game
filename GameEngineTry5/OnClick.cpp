#include "OnClick.h"
#include "ObjectContainer.h"
namespace EngineName
{
	namespace Action
	{
		bool OnClick::onClick(const unsigned int x, const unsigned int y)
		{
			mp_worldRef.
			if (mp_areaRef.boxContains(Object::Vector(x, y)))
			{
				mpf_schedule(mp_worldRef, mp_taskRef);
				return true;
			}
			return false;
		}
	}
}