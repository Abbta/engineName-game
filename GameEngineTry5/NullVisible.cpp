#include "NullVisible.h"
namespace EngineName
{
	namespace Object
	{
		//it is considered valid to tell a nullvisible to draw
			//however since it is nothing it will draw nothing
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