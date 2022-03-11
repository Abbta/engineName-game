#pragma once
#include "ObjectTasks.h"
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		template<class t_CountType, class t_TaskType> class CounterImpl;
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
			}																		//																																	//
			friend class TaskContainer;												//
		};																			//
																					//
		//*--------------------------------------------------------------------------*
	}
}