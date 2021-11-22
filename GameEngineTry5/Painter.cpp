#include "Painter.h"
#include "ObjectContainer.h"
#include "Constants.h"
#include "Visible.h"
namespace EngineName
{
	namespace Drawing
	{

		//Creates factory and rendertarget which is required for winapi painting
		void Painter::mpf_createGraphicsResources()
		{
			if (mpptr_factory == NULL)
			{
				if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpptr_factory)))
					throw Exceptions::BasicException("failed to create factory");
				RECT rc;
				GetClientRect(mp_world.mpptr_window->Window(), &rc);

				D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

				//create renderTarget
				if (FAILED(mpptr_factory->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),
					D2D1::HwndRenderTargetProperties(mp_world.mpptr_window->Window(), size),
					&mpptr_renderTarget)))
					throw Exceptions::BasicException("Failed to create render target");

				//add default color to backgroundBrush
				if (FAILED(mpptr_renderTarget->CreateSolidColorBrush(mp_backgroundColor, &mpptr_backgroundBrush)))
					throw Exceptions::BasicException("Failed to create background brush");

				if(FAILED(DWriteCreateFactory(
					DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&mpptr_writeFactory)
				)))
					throw Exceptions::BasicException("Failed to create write factory");
			}
		}

		//a function used for recursive checking of which objects to return in Painter::mpf_getAffectedObjects()
		bool Painter::mpf_modifyOverlaps(Object::Visible& object, std::vector<Object::Visible*>& returnVector, std::vector<Object::Visible>& allVector) const
		{
			bool hasModified(false);
			int lastCheckedIndex(0); //keeping track of how many indices we have iterated over, so we don't need to start over when updating iterator
			std::vector<Object::Visible>::iterator it;
			it = allVector.begin();
			while (it != allVector.end())
			{
				bool iterateNext(true); //used for turning of iterating when an element is erased
				//check if object in all overlaps object
				if (object.boxOverlaps(*it) && (object != *it))
				{
					//if it does remove it from all and add it to return
					//note that it makes it point to paintedObjects of the same layerID
					//aka how the visible was when last painted
					returnVector.push_back(&*mparr_paintedObjects[(*it).layerID]);
					it = allVector.erase(it);
					//don't iterate again
					iterateNext = false;
					//tell the outer function it needs to update its iterator
					hasModified = true;
					//call this function recursively with that object as param
					if (mpf_modifyOverlaps(*returnVector.back(), returnVector, allVector))
					{
						//if allVector has been modified
						//update it to match the new vector
						it = allVector.begin();
						//make sure we don't iterate over elements we already have iterated over
						while(it != allVector.end())
						{
							if (*it == allVector[lastCheckedIndex])
							{
								break;
							}
							it++;
						}
					}
				}
				if (it != allVector.end() && iterateNext)
				{
					it++;
					lastCheckedIndex++;
				}
			}
			return hasModified;
		}

		//gets all objects that needs repainting sorted by layerID
		std::vector<Object::Visible*> Painter::mpf_getAffectedObjects(const std::vector<std::unique_ptr<Object::Visible>>& paintObjects, const std::vector<std::unique_ptr<Object::Visible>>& allObjects) const
		{
			//make a copy of all objects
			std::vector<Object::Visible> all;
			for (auto& element : allObjects)
			{
				all.push_back(*element);
			}

			//make a return list
			std::vector<Object::Visible*> returnVector;
			for (auto& element : paintObjects)
			{
				//add paintobjects to return list
				returnVector.push_back(&*element);
			}
			
			//make temporary copy of paintObjects
			std::vector<Object::Visible> temporaryPaintObjects;
			for (auto& element : paintObjects)
			{
				temporaryPaintObjects.push_back(*element);
			}

			//remove all paintobjects from all objects
			std::vector<Object::Visible>::const_iterator it;
			it = all.begin();
			while (it != all.end())
			{
				bool iterateNext(true); //used for turning of iterating when an element is erased
				std::vector<Object::Visible>::const_iterator jt;
				jt = temporaryPaintObjects.begin();
				while(jt != temporaryPaintObjects.end())
				{
					if (*jt == *it)
					{
						it = all.erase(it);
						jt = temporaryPaintObjects.erase(jt);
						iterateNext = false;
						break;
					}
					if(jt != temporaryPaintObjects.end())
						jt++;
				}
				if (it != all.end() && iterateNext)				
					it++;
			}
			
			//for every paintObject
			for (auto& element : paintObjects)
			{
				//a function that takes one object and modifies the copied lists if they overlap
				mpf_modifyOverlaps(*element, returnVector, all);
			}


			//sort returnVector
			std::sort(returnVector.begin(), returnVector.end(), [](Object::Visible* a, Object::Visible* b) {return *a < *b; });
			
			//return
			return returnVector;
		}

		/*
		* Refresh public member function
		* If atleast 1 object wants to be painted
		* gets all affected objects
		* clears them as they were
		* repaints them as they are now
		*/
		void Painter::mf_refresh()
		{
			//mparr_objects... contains all visibles that has called their own draw() function since last draw iteration
			if (mparr_objectsThatHasCalledDraw.size() > 0)
			{
				std::vector<Object::Visible*> affectedObjects = mpf_getAffectedObjects(mparr_objectsThatHasCalledDraw, mparr_paintedObjects);

				//Begin drawing
				mpptr_renderTarget->BeginDraw();
				//----------------------------------------------------------
				//clear all affected visibles as they were
				for (int i(0); i < affectedObjects.size(); i++)
				{
					affectedObjects[i]->mpf_clear(mpptr_renderTarget, mpptr_backgroundBrush);
				}
				
				//redraw all affected objects as they are now
				for (int i(0), latestIndexOfMatchingVisible(0); i < affectedObjects.size(); i++)
				{
					if (mptr_activeObjects == nullptr)
					{
						//if no visibleGroup has been specified, all visibles are active and should be painted
						mp_world.mparr_allVisibles.at(affectedObjects[i]->layerID)->mpf_drawSelf(mpptr_renderTarget, *mpptr_brushes);
						//save a copy of the newly drawn visible in allVisibles
						mpf_addToDrawnObjects(*mp_world.mparr_allVisibles.at(affectedObjects[i]->layerID));
					}
					else
					{
						//only active visibles are affected
						mptr_activeObjects->getFromID(affectedObjects[i]->layerID, latestIndexOfMatchingVisible).mpf_drawSelf(mpptr_renderTarget, *mpptr_brushes);
						mpf_addToDrawnObjects(*mptr_activeObjects->operator[](latestIndexOfMatchingVisible));
					}
				}
				//---------------------------------------------------------
				if (FAILED(mpptr_renderTarget->EndDraw()))
					throw Exceptions::BasicException("Drawing failed");
				//Drawing is over
				mparr_objectsThatHasCalledDraw.clear();

			}
		}

		void Painter::mf_drawAll()
		{
			if (mpptr_renderTarget)
			{
				if (mptr_activeObjects == nullptr)
				{
					for (auto& element : mp_world.mparr_allVisibles)
					{
						if (element->boxCenter)
							//if element is on the screen
						{
							element->draw();
						}
					}
				}
				else
				{
					for (int i(0); i < mptr_activeObjects->size(); i++)
					{
						if (mptr_activeObjects->operator[](i)->boxCenter)
							//if element is on the screen
						{
							mptr_activeObjects->operator[](i)->draw();
						}
					}
				}
			}
		}

		void Painter::mf_addToObjectsThatHasCalledDraw(const Object::Visible& visible)
		{
			//find visible as it is in drawnobjects
			//deep copy into that has called draw
			/*
			* Old solution: Did not assume paintedObjects was sorted
			* Did not work when an early ID was not painted
			const Object::Visible* visibleAsItWas = &visible;
			for (int i(0); i < mparr_paintedObjects.size(); i++)
			{
				if (visible == *mparr_paintedObjects[i])
				{
					visibleAsItWas = &*mparr_paintedObjects[i];
				}
			}
			*/

			//New solution: Assumes paintedObjects is sorted
			//also works when early ID was not painted
			const Object::Visible* visibleAsItWas = &visible;
			if(mparr_paintedObjects.size() > visible.layerID)
				if(mparr_paintedObjects[visible.layerID])
					visibleAsItWas = &*mparr_paintedObjects[visible.layerID];

			//TODO: Fix so it works when ID has been changed
			mparr_objectsThatHasCalledDraw.push_back(std::make_unique<Object::Visible>(*visibleAsItWas)); /*deep copies visible as it was*/
		}

		void Painter::mf_clearWindow()
		{
			if (mpptr_renderTarget == nullptr)
				throw Exceptions::BasicException("Rendertarget is null");

			mpptr_renderTarget->BeginDraw();
			mpptr_renderTarget->Clear(mp_backgroundColor);
			mpptr_renderTarget->EndDraw();
		}

		void Painter::mpf_addToDrawnObjects(const Object::Visible& visible)
		{
			int elementsToBeAdded = visible.layerID - static_cast<int>(mparr_paintedObjects.size()) + 1;
			for (int i(0); i < elementsToBeAdded; i++)
			{
				//add empty spot in list
				mparr_paintedObjects.push_back(nullptr);
			}

			//add visible to drawn objects
			//as a deep copy
			mparr_paintedObjects[visible.layerID] = std::make_unique<Object::Visible>(visible);
		}

		void Painter::mf_changeBackgroundColor(const Object::Color& color)
		{
			if (mpptr_renderTarget != nullptr)
			{
				mpptr_renderTarget->CreateSolidColorBrush(color, &mpptr_backgroundBrush);
				mf_clearWindow();
				mf_drawAll();
			}
			mp_backgroundColor = color;
		}

		void Painter::mf_changeActiveScene(Object::VisibleGroup& visibleGroup)
		{
			mptr_activeObjects = &visibleGroup;
		}
	}
}