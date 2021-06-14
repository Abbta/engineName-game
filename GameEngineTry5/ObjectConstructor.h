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
			void mf_registerNewVisible(Visible& visible);
			void mf_makeRoomForNewVisible();
		public:
			ObjectConstructor(Base::ObjectContainer &world): mp_world(world) {}
			ObjectConstructor(Base::ObjectContainer* world) : mp_world(*world) {}
		};
	}
}