#include "BaseIncludeLibraries.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		/*
		* object class
		* template for all objects that can be added to world
		* contains variables and functions that all addable objects must have
		*/
		class Object
		{
		protected:
			//ref to world object
			Base::ObjectContainer* mptr_world;
		protected:
			//is only to be constructed by children
			Object(Base::ObjectContainer& world) : mptr_world(&world) {}
		};
	}
}

