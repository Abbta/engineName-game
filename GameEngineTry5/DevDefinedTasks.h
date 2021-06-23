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

		class TaskContainer
		{
		private:
			friend class Base::ObjectContainer;

			std::list<Move> mparr_move;
			Move& mpf_add(const Move& task) 
			{ 
				mparr_move.push_back(task);
				mparr_move.back().mptr_storageRef = &mparr_move;
				std::list<Move>::iterator it = mparr_move.end();
				it--;
				mparr_move.back().mpit_storageItRef = it;
				return mparr_move.back();
			}

			//add storages and overloads of add function to your tasks:
			//*-----------------------------------------------------------------*

			std::list<myClass> myArray;
			Task& mpf_add(myClass& task) 
			{
				myArray.push_back(task);
				myArray.back().mptr_storageRef = &myArray;
				myArray.back().mpit_storageItRef = myArray.end();
				return mparr_move.back(); 
			}

			//*-----------------------------------------------------------------*
			friend class Action::OnActionBase;
		};

	}
}