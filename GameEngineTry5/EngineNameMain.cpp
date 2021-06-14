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
	world.circle.build(world, Vector(5, 3), 7);
	world.circle.build(world, Vector(17, 50), 10);
	EngineName::Object::Rectangle *r = &world.rectangle.build(world, Vector(20, 54), 11, 11, Color("FF0000"));
	world.circle.build(world, Vector(117, 50), 10);
	world.rectangle.build(world, Vector(0, 0), 1000, 200, Color("0000FF")).layerID = 0;
	world.textRectangle.build(EngineName::Object::Rectangle(world, Vector(250, 250), 100, 60, Color("FFDDDD")), L"Hejsan hoppsan");

	world.schedule(Move(*r, Vector(200, 100)), 1000);
	return world.size();
}