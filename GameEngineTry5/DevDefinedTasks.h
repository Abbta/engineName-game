#include "BaseIncludeLibraries.h"
#include "ObjectTasks.h"
#pragma once
namespace EngineName
{
	namespace Action
	{
		class OnActionBase;
	}
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Time
	{

		//Define your custom tasks here:
		//Use the following as base:
		//*--------------------------------------------------------------------------*
																					//
		class myClass : public Task													//
		{																			//
		private:																	//
			std::list<myClass>* mptr_storageRef;									//
			std::list<myClass>::iterator mpit_storageItRef;							//
			void mpf_perform(Base::ObjectContainer& world) override					//
			{																		//
				//Write custom perform code here (or in devDefinedTasks.cpp):		//
				//*-------------------------*										//
																					//
				throw Exceptions::BasicException("Custom class perform called");	//
																					//
				//*-------------------------*										//
			}																		//
																					//
			virtual void Destroy() override											//
			{																		//
				mptr_storageRef->erase(mpit_storageItRef);							//
			}																		//
																					//
			friend class TaskContainer;												//
		};																			//
																					//
		//*--------------------------------------------------------------------------*
	}
}