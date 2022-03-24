#include "ObjectContainer.h"
#include "ObjectContainerAccess.h"

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
using namespace EngineName;

/*
* Main function
* consider this as the start of execution
* here you can add your own objects using world.objectType.build()
* get the full list of objecttypes and other functions by typing world. in an IDE
*/
int engineNameMain(Base::ObjectContainer &world)
{
	//register all objects

	world.backgroundColor = Object::Color("AAAAFF");


	Object::Scene* gameScene = &world.scene.build(world);
	gameScene->add(world.rectangle.build(world, Object::Vector((world.width / 2.0) - 39, 0), 78, 42, Object::Color("567556")));
	auto topDisplay = &world.display.build(
		Object::TextRectangle(
			Object::Rectangle(world, Object::Vector((world.width / 2.0) - 5, 9), 10, 19, Object::Color("567556")), L"", Drawing::Font(L"Open Sans", 18U)),
		0);
	gameScene->add(*topDisplay);
	gameScene->add(world.button.build(Object::Button(
		Object::Rectangle(world, Object::Vector((world.width / 2.0) - 7, 45), 14, 8, Object::Color("992343")),
		Time::AddToCounter<int>(topDisplay->counter(), 1)
	)));
	gameScene->add(world.activatableTextButton.build(
		Object::ActivatableTButton(
			Object::TextRectangle(
				Object::Rectangle(world, Object::Vector(350, 50), 125, 28, Object::Color("55D314")),
				L"Active",
				Drawing::Font(L"Open Sans", 14)
			),
			Object::TextRectangle(
				Object::Rectangle(world, Object::Vector(350, 50), 125, 28, Object::Color("FA9314")),
				L"Inactive",
				Drawing::Font(L"Open Sans", 14)
			),
			Time::AddToCounter<int>(topDisplay->counter(), 1),
			true
		)
	));

	
	Object::Scene* mainMenuScene = &world.scene.build(world);
	auto menuRect = &world.rectangle.build(world, Object::Vector((world.width * (3 / 8.0)), (world.height * (1/6.0))), world.width * (2/8.0), world.height * (4/7.0), Object::Color("333355"));
	mainMenuScene->add(*menuRect);
	const EngineName::Object::Rectangle buttonRectangle(
		world,
		Object::Vector(world.width * (7 / 16.0), world.height * (3 / 12.0)),
		world.width * (2 / 16.0),
		world.height * (1 / 16.0),
		Object::Color("AA5678"));
	const EngineName::Time::ChangeActiveScene buttonAction(*gameScene);
	EngineName::Object::Button tempButton(buttonRectangle, buttonAction);
	const EngineName::Drawing::Font buttonFont(L"Open Sans", 22U);
	EngineName::Object::TextButton tempTextButton(tempButton, L"Hello World", buttonFont);
	auto button = &world.textButton.build(tempTextButton);
	
	mainMenuScene->add(*button);


	world.setActiveScene(*mainMenuScene);

	return world.size();
}