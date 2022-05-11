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
			//if factory has not been created
			if (mpptr_factory == NULL)
			{
				//create factory
				if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpptr_factory)))
					throw Exceptions::BasicException("failed to create factory");

				//calculate size of window
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

			}
			//if write factory has not been created
			if(mpptr_writeFactory == NULL)
			{
				//create write factory
				if(FAILED(DWriteCreateFactory(
					DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&mpptr_writeFactory)
				)))
					throw Exceptions::BasicException("Failed to create write factory");
			}
		}

		/*
		* modify overlaps member function
		* a function used for recursive checking of which objects to return in Painter::mpf_getAffectedObjects()
		* Takes 3 parameters
		*	Object: The visible that we are checking for overlaps
		*	returnVector: a vector of ptrs to visibles, will in the end contain refs to
		*		all visibles that in some way overlap those that are to be repainted.
		*		The ptrs points to visibles as they were when last drawn
		*	allVector: a vector of ptrs to all visibles affected by this redraw that has not been added to returnvector.
		*		As an element is added to returnvector, it is removed from allVector. Allvector points to
		*			the vector of all elements as they were when last painted
		* 
		* Returns bool
		*	true if allvector has been change, meaning that the function one step outside in the recursion
		*		will need to update its allVector iterator so that it is not reiterating over the same objects
		*/
		bool Painter::mpf_modifyOverlaps(Object::Visible& object, std::vector<Object::Visible*>& returnVector, std::vector<Object::Visible*>& allVector) const
		{
			bool hasModified(false); //keeps track of if allvector has been modified
			int lastCheckedIndex(0); //keeping track of how many indices we have iterated over, so we don't need to start over when updating iterator

			//iterate over allVector to see what elements overlap object
			std::vector<Object::Visible*>::iterator it;
			it = allVector.begin();
			while (it != allVector.end())
			{
				bool iterateNext(true); //used for turning of moving to the next iterator when an element is erased
				//check if object in all overlaps object
				if (object.boxOverlaps(**it) && (object != **it))
				{
					//if it does remove it from all and add it to return
					//note that it makes it point to paintedObjects of the same layerID
					//aka how the visible was when last painted
					returnVector.push_back(&*mparr_paintedObjects[(*it)->layerID]);
					it = allVector.erase(it);

					//don't iterate again
					iterateNext = false;
					//tell the outer function it needs to update its iterator
					hasModified = true;

					//save what the allVector looked like before next modifyOverlaps was called
						//we only care about elements we have already checked
					std::vector<Object::Visible*> allVectorBeforeChange;
					for (int i(0); i <= lastCheckedIndex; i++)
					{
						//add a new pointer to the same element of allVisibles as in that index of allVector
						allVectorBeforeChange.push_back(&*allVector[i]);
					}

					//call this function recursively with that object as param
						//if an element overlaps, we need to check what overlapps that element in the exact same way
					if (mpf_modifyOverlaps(*returnVector.back(), returnVector, allVector))
					{
						//if allVector has been modified
						//update iterator to match the new vector
						it = allVector.begin();
						//make sure we don't iterate over elements we already have iterated over
						int iii(0);
						while(it != allVector.end() && iii < lastCheckedIndex)
						{
							//iterate until allVector no longer matches allVector before change
							if (*allVectorBeforeChange[iii] != *allVector[iii])
							{
								break;
							}
							//every successful iteration here means we don't need to iterate it again in this level of the recursion
								//until allvector is changed again
							it++;
							iii++;
						}
					}
				}
				if (it != allVector.end() && iterateNext)
				{
					//avoid iterating past the end or skipping an element due to the vector being changed
					it++;
					lastCheckedIndex++;
				}
			}
			//return if allVector has been modified
			return hasModified;
		}

		/*
		* get affected objects member function
		* gets all objects that needs repainting sorted by layerID
		* Takes two params
		*	paintObjects, a vector of all objects that wants to be repainted
		*		as they were when they were last painted, and as they are now if they have moved.
		*		These two spots need to be cleared and then repainted in order to get the correct layering
		*	allObjects, a vector of all visibles in the active scene
		* returns a new vector of ptrs to all visibles that directly or inderectly overlaps paintobjects.
		*	If a visible overlaps one of those who is to be repainted, it will also need to be repainted and we need to include
		*		the visibles that overlaps it and so forth
		*	The ptrs point to the visibles as they were, if there is a difference the visible should already be in paintObjects
		*		and there should be no issue with this. Atleast none has been found yet
		*/
		std::vector<Object::Visible*> Painter::mpf_getAffectedObjects(const std::vector<std::unique_ptr<Object::Visible>>& paintObjects, const std::vector<std::unique_ptr<Object::Visible>>& allObjects) const
		{
			//make a copy of all objects
			std::vector<Object::Visible*> all;
			for (auto& element : allObjects)
			{
				all.push_back(&*element);
			}

			//make a return list
			std::vector<Object::Visible*> returnVector;
			for (auto& element : paintObjects)
			{
				//add paintobjects to return list as we already know they will need to be repainted
				returnVector.push_back(&*element);
			}

			//remove paintObjects from all objects
			//make temporary copy of paintObjects
			std::vector<Object::Visible*> temporaryPaintObjects;
			for (auto& element : paintObjects)
			{
				temporaryPaintObjects.push_back(&*element);
			}
			//iterate through allObjects
			std::vector<Object::Visible*>::const_iterator it;
			it = all.begin();
			while (it != all.end())
			{
				bool iterateNext(true); //used for turning of iterating when an element is erased, as to not skip any elements

				//for every allObject, check if it is the same as any of the elements in paintObjects
				std::vector<Object::Visible*>::const_iterator jt;
				jt = temporaryPaintObjects.begin();
				while(jt != temporaryPaintObjects.end())
				{
					if (**jt == **it)
					{
						//if an element is in both vectors
						//remove it from all
						it = all.erase(it);
						//also remove it from temp as there should be no other element ín all that matches
						jt = temporaryPaintObjects.erase(jt);
						iterateNext = false;
						//as only one in temp matches the one in all, we don't need to check in temp anymore
						break;
					}
					if(jt != temporaryPaintObjects.end())
						jt++;
				}
				if (it != all.end() && iterateNext)				
					it++;
			}
			
			//get all elements that is affected by paintObjects
			for (auto& element : paintObjects)
			{
				//a function that takes one object and modifies the copied lists if they overlap.
					//Also recursively checks for overlapping elements on the overlapping and so on
				mpf_modifyOverlaps(*element, returnVector, all);
			}


			//sort returnVector by layerID
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
				//has a copy of the objects as they were but also as they are now if they have moved
			if (mparr_objectsThatHasCalledDraw.size() > 0 && mpptr_renderTarget)
			{
				//get all visibles that are affected by the visibles requesting draw.
					//I.e all visibles that directly or inderectly overlap the boxes of these
				//The return vector is the visibles as they were (+as they are now for those requesting draw and having moved)
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
					//lastIndexOfMatchingVisible is used for optimisation in visibleGroup::getFromId()
				for (int i(0), latestIndexOfMatchingVisible(0); i < affectedObjects.size(); i++)
				{
					if (mptr_activeObjects == nullptr)
					{
						//if no visibleGroup has been specified, all visibles are active and should be painted
						mp_world.mparr_allVisibles.at(affectedObjects[i]->layerID)->mpf_drawSelf(mpptr_renderTarget, *mpptr_brushes);
						//save a copy of the newly drawn visible in allVisibles
						mpf_addToDrawnObjects(*mp_world.mparr_allVisibles.at(affectedObjects[i]->layerID));
						//note that the visibles that has called draw are called twice here
							//but this doesn't affect much as they both refer to the same object in allVisibles
							//i.e the same object is added twice
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
				//clear vector
				mparr_objectsThatHasCalledDraw.clear();

			}
		}

		/*
		* Draw all member function
		* makes all visibles in the active scene request painting
		* is called after mainwindow has been rendered and after scene
		*	has been switched
		* if no scene is selected, it draws all visibles
		*/
		void Painter::mf_drawAll()
		{
			//prevent it from asking a visible to draw before rendertarget has been set
			if (mpptr_renderTarget)
			{
				//if we have no active scene
				if (mptr_activeObjects == nullptr)
				{
					//all visibles
					for (auto& element : mp_world.mparr_allVisibles)
					{
						if (element->boxCenter)
							//if element is on the screen
						{
							//ask to draw
							element->draw();
						}
					}
				}
				else
				{
					//if we have an active scene
					//for all visibles in that scene
					for (int i(0); i < mptr_activeObjects->size(); i++)
					{
						if (mptr_activeObjects->operator[](i)->boxCenter)
							//if element is on the screen
						{
							//ask to draw
							mptr_activeObjects->operator[](i)->draw();
						}
					}
				}
			}
		}

		/*
		* Add to objects that has called draw member function
		* takes a ref to a visible and adds a copy of it
		*	as it was when last painted and a copy of how it
		*	is now and adds it to objectsThatHasCalledDraw
		*/
		void Painter::mf_addToObjectsThatHasCalledDraw(const Object::Visible& visible)
		{
			//find visible as it is in drawnobjects
			//deep copy into that has called draw

			//Assumes paintedObjects is sorted
			//also works when early ID was not painted

			//presumes visible is the same as as it was
			const Object::Visible* visibleAsItWas = &visible;
			//however if there exists a non null visible in paintedObjects that matches this visibles's ID,
				//that visible will certainly be visible as it was
			if(mparr_paintedObjects.size() > visible.layerID)
				if(mparr_paintedObjects[visible.layerID]->layerID != 0) //0 is nullvisible
					visibleAsItWas = &*mparr_paintedObjects[visible.layerID];

			//Add a copy of visible as it was and visible as it is to objectsThatHasCalledDraw
			//TODO: Fix so it works when ID has been changed
			mparr_objectsThatHasCalledDraw.push_back(std::make_unique<Object::Visible>(*visibleAsItWas)); /*deep copies visible as it was*/
			mparr_objectsThatHasCalledDraw.push_back(std::make_unique<Object::Visible>(visible));		  /*deep copies visible as it is now*/
		}

		/*
		* clearWindow member function
		* Graphically clears all currently painted visibles
		* Creates a drawing context of its own
		* Takes no regard to active objects and so on, just does the graphical clear
		*/
		void Painter::mf_clearWindow()
		{
			if (mpptr_renderTarget == nullptr)
				return;

			mpptr_renderTarget->BeginDraw();
			mpptr_renderTarget->Clear(mp_backgroundColor);
			mpptr_renderTarget->EndDraw();
		}

		/*
		* Add to drawn objects member function
		* Takes visible as param
		* Adds a copy of this visible to the index in paintedObjects matching the visibles ID
		* Adds empty spots to paintedObjects if neccessary
		* 
		* This copy is used to know how the visible looks like right now but at next draw (visible as it was)
		*/
		void Painter::mpf_addToDrawnObjects(const Object::Visible& visible)
		{
			//if non negative, is how many objects that needs to be added in order for
				//the last one to match ID of visible
			int elementsToBeAdded = visible.layerID - static_cast<int>(mparr_paintedObjects.size()) + 1;
			for (int i(0); i < elementsToBeAdded; i++)
			{
				//add empty spot in list
				mparr_paintedObjects.push_back(std::make_unique<Object::Visible>(mp_world.nullVisible));
				//nullvisible is a static visible representing null
			}

			//add visible to drawn objects
			//as a deep copy
			mparr_paintedObjects[visible.layerID] = std::make_unique<Object::Visible>(visible);
		}

		/*
		* change background color member function
		* changes the background color on screen to param
		* also redraws all objects
		*/
		void Painter::mf_changeBackgroundColor(const Object::Color& color)
		{
			//if rendertarget has been set, we can perform the actual drawing
			if (mpptr_renderTarget != nullptr)
			{
				//changes backgroundbrush into a brush of the given color
				mpptr_renderTarget->CreateSolidColorBrush(color, &mpptr_backgroundBrush);
				//redraws all objects
				mf_clearWindow();
				mf_drawAll();
			}
			//changes variable that is used to get information about what the current background color is
			mp_backgroundColor = color;
		}

		//changes active scene, does no painting of its own
		void Painter::mf_changeActiveScene(Object::VisibleGroup& visibleGroup)
		{
			mptr_activeObjects = &visibleGroup;
		}

		//gets a ptr to visible group of active visibles
		const Object::VisibleGroup* Painter::mf_getActiveScene() const
		{
			return mptr_activeObjects;
		}
	}


}