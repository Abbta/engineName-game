#include "TextRectangle.h"
#include "BrushContainer.h"
#include "ObjectContainerAccess.h"
#include "Painter.h"
#define painter Base::ObjectContainerAccess::getPainter(*mptr_world)
namespace EngineName
{
	namespace Object
	{
		void TextRectangle::mpf_drawSelf(CComPtr<ID2D1HwndRenderTarget>& renderTarget, Drawing::BrushContainer& brushes) const
		{
			renderTarget->FillRectangle(*this, (brushes.getBrush(renderTarget, color)));

			if (borderWidth > 0)
			{
				renderTarget->DrawRectangle(*this, brushes.getBrush(renderTarget, color), static_cast<FLOAT>(borderWidth));
			}

			renderTarget->DrawTextW(
				mp_text.c_str(),
				static_cast<UINT32>(mp_text.length()),
				painter.mpptr_fonts->getFont(painter.mpptr_writeFactory, mp_font),
				*this,
				brushes.getBrush(renderTarget, mp_textColor));
		}
	}
}