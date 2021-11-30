#include "NullVisible.h"
namespace EngineName
{
	namespace Object
	{
		void NullVisible::mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const
		{
			return;
		}

		void NullVisible::draw() const
		{
			return;
		}
	}
}