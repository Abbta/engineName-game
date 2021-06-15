#include "ObjectContainer.h"

//for debugging
#include "Circle.h"
#include "Rectangle.h"
#include "Vector.h"
#include "ObjectTasks.h"
#include "TextRectangle.h"
using namespace EngineName::Object;
using namespace EngineName::Time;

/*
* Main function
* consider this as the start of execution
* here you can add your own objects using world.objectType.new()
* get the full list of objecttypes and other functions by typing world. in an IDE
*/
int engineNameMain(EngineName::Base::ObjectContainer &world)
{
	//register all objects

	world.backgroundColor = Color("AAAAFF");
	world.rectangle.build(world, Vector(0, 0), 100, 60, Color("000000"));

	return world.size();
}