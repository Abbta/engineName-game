#pragma once
namespace EngineName
{
	namespace Base
	{
		class ObjectContainer;
	}
	namespace Object
	{
		class Visible;
		/*
		* objectconstructor class
		* base for classes used for dev construction of objects
		* contains a ref to world
		*/
		class ObjectConstructor
		{
		private:
			Base::ObjectContainer& mp_world;
		protected:
			//signals that a new unique visible is to be constructed
			void mf_makeRoomForNewVisible();
			//adds visible to list of all visibles
			void mf_registerNewVisible(Visible& visible);
		public:
			ObjectConstructor(Base::ObjectContainer* world) : mp_world(*world) {}
		};
	}
}