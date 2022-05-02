#pragma once
#include "ObjectConstructor.h"
#include "DisplayImpl.h"
namespace EngineName
{
    namespace Object
    {
        /*
        * Display constructor class
        * Used for constructing display
        * Has .build()
        *   Special case:
        *       constructs the implemented object from a template dynamically
        *       demotes it to Display base class ptr and lets a unique_ptr handle it
        *       places it in list
        *       gives back ref
        * Stores all displays within itself
        *   all displays are stored in the same list, regardless of type
        */
        class DisplayConstructor :
            public ObjectConstructor
        {
        private:
            //Note that the displays are parents to displayImpl templates
            std::list<std::unique_ptr<Display>> mparr_allDisplays;
        public:
            DisplayConstructor(Base::ObjectContainer* world) : ObjectConstructor(world) {};

            //note that build is templated
            template<class t_CountType> Display& build(const DisplayImpl<t_CountType>& display)
            {
                //adds an empty spot in allvisibles, this signals that a new unique 
                    //visible is constructed meaning it needs a unique layerID
                this->mf_makeRoomForNewVisible();
                //construct the implemented part in dynamic memory
                DisplayImpl<t_CountType>* tempImplementedPart = new DisplayImpl<t_CountType>(display);
                //demote it to an object of common type and store all in the same container
                mparr_allDisplays.push_back(std::unique_ptr<Display>(tempImplementedPart));
                //add to all visibles
                this->mf_registerNewVisible(*mparr_allDisplays.back());

                //also: make updateDisplay task fire so that it updates its text to correct number
                (*mparr_allDisplays.back()).counter() += 0;

                return *mparr_allDisplays.back();
            }

            //overload of above
            template<class t_CountType> Display& build(const TextRectangle& textRectangle, const t_CountType& initialCount = 0)
            {
                this->mf_makeRoomForNewVisible();
                DisplayImpl<t_CountType>* tempImplementedPart = new DisplayImpl<t_CountType>(Display(textRectangle), initialCount);
                mparr_allDisplays.push_back(std::unique_ptr<Display>(tempImplementedPart));
                this->mf_registerNewVisible(*mparr_allDisplays.back());

                //also: make updateDisplay task fire so that it updates its text to correct number
                (*mparr_allDisplays.back()).counter() += 0;

                return *mparr_allDisplays.back();
            }
        };
    }
}

