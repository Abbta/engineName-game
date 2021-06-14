#include "BrushContainer.h"
namespace EngineName
{
	namespace Drawing
	{
		/*
		* Getbrush member function
		* Takes ptr to rendertarget and color
		* If there already exists a brush with the given color, it is returned
		* Otherwise a new brush with that color is constructed and then returned
		*/
		CComPtr<ID2D1SolidColorBrush>& BrushContainer::getBrush(CComPtr<ID2D1HwndRenderTarget>& renderTarget, const Object::Color& solidColor)
		{
			if (renderTarget == nullptr)
				throw Exceptions::BasicException("render target is nullptr");

			//get brush-string pair iterator
				//first is string, second is brush
			std::map<std::string, CComPtr<ID2D1SolidColorBrush>>::iterator brushPair = mpmap_solidBrushes.find(solidColor);

			if (brushPair == mpmap_solidBrushes.end())
				//if brush doesn't exist
			{
				//add an empty brush-string pair to solidbrushes and store it
				std::map<std::string, CComPtr<ID2D1SolidColorBrush>>::iterator newBrushPair = mpmap_solidBrushes.emplace(solidColor, CComPtr<ID2D1SolidColorBrush>(nullptr)).first;

				//add color to the brush
				if(FAILED(renderTarget->CreateSolidColorBrush(solidColor, &(newBrushPair->second))))
					throw Exceptions::BasicException("Failed creating brush");

				//get the newly constructed brush
				brushPair = newBrushPair;
			}

			return brushPair->second;
		}
	}
}