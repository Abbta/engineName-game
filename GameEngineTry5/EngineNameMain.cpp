#include "ObjectContainer.h"

//for debugging
#include "Circle.h"
#include "Rectangle.h"
#include "Vector.h"
#include "ObjectTasks.h"
#include "TextRectangle.h"
#include "OnClick.h"
#include "Button.h"
using namespace EngineName::Object;
using namespace EngineName::Time;

/*
* Main function
* consider this as the start of execution
* here you can add your own objects using world.objectType.build()
* get the full list of objecttypes and other functions by typing world. in an IDE
*/
int engineNameMain(EngineName::Base::ObjectContainer &world)
{
	//register all objects

	world.backgroundColor = Color("AAAAFF");
	world.rectangle.build(world, Vector((world.width * (3 / 8.0)), (world.height * (1/6.0))), world.width * (2/8.0), world.height * (4/7.0), Color("333355"));
	const EngineName::Object::Rectangle buttonRectangle(
		world,
		Vector(world.width * (7 / 16.0), world.height * (3 / 12.0)),
		world.width * (5 / 16.0),
		world.height * (1 / 10.0),
		Color("AA5678"));
	EngineName::Object::Visible tempRef(buttonRectangle);
	const EngineName::Time::Move buttonAction(tempRef, Vector(50, 0));
	EngineName::Object::Button tempButton(buttonRectangle, buttonAction);
	auto button = world.button.build(tempButton);
	button.changeOnClickTask(EngineName::Time::Move(button, Vector(50, 0)));

	return world.size();
}