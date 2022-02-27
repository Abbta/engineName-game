#pragma once
#include "ObjectTasks.h"
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
				if(mp_isDestructable)												//
					mptr_storageRef->erase(mpit_storageItRef);						//
			}																		//
																					//
			friend class TaskContainer;												//
		};																			//
																					//
		//*--------------------------------------------------------------------------*

		//TaskContainer
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

			std::list<ChangeActiveScene> mparr_changeActiveScene;
			ChangeActiveScene& mpf_add(const ChangeActiveScene& task)
			{
				mparr_changeActiveScene.push_back(task);
				mparr_changeActiveScene.back().mptr_storageRef = &mparr_changeActiveScene;
				std::list<ChangeActiveScene>::iterator it = mparr_changeActiveScene.end();
				it--;
				mparr_changeActiveScene.back().mpit_storageItRef = it;
				return mparr_changeActiveScene.back();
			}
			
			std::list<UpdateDisplay> mparr_updateDisplay;
			UpdateDisplay& mpf_add(const UpdateDisplay& task)
			{
				mparr_updateDisplay.push_back(task);
				mparr_updateDisplay.back().mptr_storageRef = &mparr_updateDisplay;
				std::list<UpdateDisplay>::iterator it = mparr_updateDisplay.end();
				it--;
				mparr_updateDisplay.back().mpit_storageItRef = it;
				return mparr_updateDisplay.back();
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
			template<class t_CountType, class t_taskType> friend class Object::CounterImpl;
		};

	}
}