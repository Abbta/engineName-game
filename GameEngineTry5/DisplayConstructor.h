#pragma once
#include "ObjectConstructor.h"
#include "DisplayImpl.h"
namespace EngineName
{
    namespace Object
    {
        class DisplayConstructor :
            public ObjectConstructor
        {
        private:
            std::list<std::unique_ptr<Display>> mparr_allDisplays;
        public:
            DisplayConstructor(Base::ObjectContainer& world) : ObjectConstructor(world) {};
            DisplayConstructor(Base::ObjectContainer* world) : ObjectConstructor(*world) {};

            template<class t_CountType> Display& build(const DisplayImpl<t_CountType>& display)
            {
                this->mf_makeRoomForNewVisible();
                DisplayImpl<t_CountType>* tempImplementedPart = new DisplayImpl<t_CountType>(display);
                mparr_allDisplays.push_back(std::unique_ptr<Display>(tempImplementedPart));
                this->mf_registerNewVisible(*mparr_allDisplays.back());

                //also: make updateDisplay task fire so that it updates its text to correct number
                (*mparr_allDisplays.back()).counter() += 0;

                return *mparr_allDisplays.back();
            }

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

