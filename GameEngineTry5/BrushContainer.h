#include "BaseIncludeLibraries.h"
#include "GraphicsIncludeLibraries.h"
#include "Color.h"
#pragma once
namespace EngineName
{
	namespace Drawing
	{
		/*
		* Brush container class
		* Contains a map with colors mapped with strings representing them as hex
		* Contains the getBrush function which either returns an existing brush or creates and returns a new brush
		*/
		class BrushContainer
		{
		private:
			std::map<std::string, CComPtr<ID2D1SolidColorBrush>> mpmap_solidBrushes;
		public:
			//gets the specified brush or creates it if it doesn't exist
			CComPtr<ID2D1SolidColorBrush>& getBrush(CComPtr<ID2D1HwndRenderTarget>& renderTarget, const Object::Color& solidColor);
		};
	}
}

