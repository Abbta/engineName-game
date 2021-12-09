#include "ObjectContainer.h"

//for debugging
#include "Circle.h"
#include "Rectangle.h"
#include "Vector.h"
#include "ObjectTasks.h"
#include "TextRectangle.h"
#include "OnClick.h"
#include "Button.h"
#include "Scene.h"
#include "Counter.h"
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


	Scene* gameScene = &world.scene.build(world);
	gameScene->add(world.rectangle.build(world, Vector(56, 6), 100, 100, Color("FF0000")));
	
	Scene* mainMenuScene = &world.scene.build(world);
	auto menuRect = &world.rectangle.build(world, Vector((world.width * (3 / 8.0)), (world.height * (1/6.0))), world.width * (2/8.0), world.height * (4/7.0), Color("333355"));
	mainMenuScene->add(*menuRect);
	Move testMove(*menuRect, Vector(100, 5));
	EngineName::Object::Counter<int, Move> testCounter(world, 5, &testMove);
	testCounter += 3;
	const EngineName::Object::Rectangle buttonRectangle(
		world,
		Vector(world.width * (7 / 16.0), world.height * (3 / 12.0)),
		world.width * (2 / 16.0),
		world.height * (1 / 16.0),
		Color("AA5678"));
	const EngineName::Time::ChangeActiveScene buttonAction(*gameScene);
	EngineName::Object::Button tempButton(buttonRectangle, buttonAction);
	const EngineName::Drawing::Font buttonFont(L"Open Sans", 22U);
	EngineName::Object::TextButton tempTextButton(tempButton, L" New Game", buttonFont);
	auto button = &world.textButton.build(tempTextButton);
	
	mainMenuScene->add(*button);


	world.setActiveScene(*mainMenuScene);

	return world.size();
}