#include "BaseIncludeLibraries.h"
#include "ObjectTasks.h"
#pragma once
namespace EngineName
{
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
		private:																	//					//
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