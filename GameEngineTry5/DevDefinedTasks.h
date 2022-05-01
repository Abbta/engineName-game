#pragma once
#include "ObjectTasks.h"
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
		private:																	//					
			void mpf_perform(Base::ObjectContainer& world) override					//
			{																		//
				//Write custom perform code here (or in devDefinedTasks.cpp):		//
				//*-------------------------*										//
																					//
				throw Exceptions::BasicException("Custom class perform called");	//
																					//
				//*-------------------------*										//
			}																		//			
			//Taskcontainer needs access to perform									//
			friend class TaskContainer;												//
		};																			//
																					//
		//*--------------------------------------------------------------------------*
	}
}