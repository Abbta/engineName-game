#include "GraphicsIncludeLibraries.h"
#include "BaseIncludeLibraries.h"
#include "BrushContainer.h"
#include "TextFormatContainer.h"
#include "Color.h"
#include "Visible.h"
#include "VisibleGroup.h"
#include "Constants.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		class TextRectangle;
	}
	namespace Drawing
	{
		/*
		* painter class
		* is friend of objectcontainer class
		* class for handling all graphic output
		* contains brushes and factories
		* contains the rendertarget which handles winapi painting
		*	but the objects paints themselves with own functions
		* contains a vector (possibly a map) with all visible objects on screen
		*	as they were when last painted
		* conatians a function which takes an array of visibles and gives back an array of the visibles that needs to be redrawn
		*
		* Drawing from object:
		*	During the latest loop, one or more visibles has calld their own .paint() which stores a ref to them in a vector member inside Painter.
		*	This vector is then passed to a function which returns a vector with all visibles that need to be repainted.
		*		The returned vector is based on the vector of all objects as they were when last painted
		*	All of these visibles are then passed to a function which clears them
		*	The vector with all visibles are then uppdated with the objects that are to be repainted
		*	From this updated vector, all affected visibles are drawn
		*/
		class Painter
		{
		private:
			CComPtr<ID2D1HwndRenderTarget>		 mpptr_renderTarget;
			CComPtr<ID2D1Factory>				 mpptr_factory;
			std::unique_ptr<BrushContainer>		 mpptr_brushes; //unsure if it really needs to be dynamically allocated
			CComPtr<ID2D1SolidColorBrush>		 mpptr_backgroundBrush; //brushed used for clearing visibles
			CComPtr<IDWriteFactory>				 mpptr_writeFactory;
			std::unique_ptr<TextFormatContainer> mpptr_fonts;
			void mpf_createGraphicsResources(); //allocates graphic resources

			Object::Color mp_backgroundColor;

			std::vector<std::unique_ptr<Object::Visible>> mparr_paintedObjects; //All visibles as they were when last painted
			std::vector<std::unique_ptr<Object::Visible>> mparr_objectsThatHasCalledDraw; //Visibles that wants to be drawn as they were
			std::vector<Object::Visible*> mpf_getAffectedObjects(
				const std::vector<std::unique_ptr<Object::Visible>>& paintObjects,
				const std::vector<std::unique_ptr<Object::Visible>>& allObjects
			) const; //returns all visibles that overlaps visivles in paintObjects
			void mpf_addToDrawnObjects(const Object::Visible& visible); //add an object to paintedObjects
			bool mpf_modifyOverlaps(Object::Visible& object, std::vector<Object::Visible*>& returnVector, std::vector<Object::Visible>& allVector) const; //used for determining which visibles to draw

			Object::VisibleGroup* mptr_activeObjects; //ptr to visibleGroup that is to be shown on screen, null means all visibles are active
			Base::ObjectContainer& mp_world; //ref to world
		public:
			Painter(Base::ObjectContainer& world) :
				mp_world(world), mpptr_renderTarget(nullptr), mpptr_factory(nullptr), mpptr_backgroundBrush(nullptr),
				mpptr_brushes(std::make_unique<BrushContainer>(BrushContainer())),
				mpptr_writeFactory(nullptr), mpptr_fonts(std::make_unique<TextFormatContainer>(TextFormatContainer())),
				mp_backgroundColor(Object::c_defaultBackgroundColor), mptr_activeObjects(nullptr)
			{}
			/*
			Painter(Painter& p): 
				mp_world(p.mp_world), mpptr_renderTarget(p.mpptr_renderTarget), mpptr_factory(p.mpptr_factory),
				mpptr_backgroundBrush(p.mpptr_backgroundBrush), mpptr_brushes(std::make_unique<Drawing::BrushContainer>(*(p.mpptr_brushes))) {}

			Painter(Painter* p):
				mp_world(p->mp_world), mpptr_renderTarget(p->mpptr_renderTarget), mpptr_factory(p->mpptr_factory),
				mpptr_backgroundBrush(p->mpptr_backgroundBrush), mpptr_brushes(std::make_unique<Drawing::BrushContainer>(*(p->mpptr_brushes))) {}*/

			void mf_refresh(); //Paints everything that has reqested painting
			void mf_createGraphicsResources() { mpf_createGraphicsResources(); } //public accessor to creatGr
			void mf_drawAll(); //Makes all visibles request painting (used first time window is opened for example)
			void mf_addToObjectsThatHasCalledDraw(const Object::Visible& visible); //used for requesting paint
			void mf_clearWindow(); //clears all visibles
			void mf_changeBackgroundColor(const Object::Color& color);
			void mf_changeActiveScene(Object::VisibleGroup& visibleGroup);

			friend class Object::TextRectangle;
		};
	}
}

