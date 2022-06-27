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
#include "Shape.h"
using namespace EngineName;

/*
* Main function
* consider this as the start of execution
* here you can add your own objects using world.objectType.build()
* get the full list of objecttypes and other functions by typing world. in an IDE
*/
int engineNameMain(Base::ObjectContainer &world)
{
	//register all objects:
	//----------------------------------------------------------
	//this is a sample world structure
	//user defined colours
	const auto c_backgroundColor = Object::Color("AAAAFF");
	const auto c_displayColorGreen = Object::Color("567556");
	const auto c_buttonColorGreen = Object::Color("55D314");
	const auto c_buttonColorRedA = Object::Color("FA9314");
	const auto c_buttonColorRedB = Object::Color("992343");
	
	const auto c_mainMenuRectColor = Object::Color("333355");
	const auto c_startButtonColor = Object::Color("AA5678");

	
	//user defined fonts
	const auto c_displayFont = Drawing::Font(L"Open Sans", 18U);
	const auto c_buttonFontA = Drawing::Font(L"Open Sans", 14);

	const auto c_buttonFontB = Drawing::Font(L"Open Sans", 22U);


	//change background colour
	world.backgroundColor = c_backgroundColor;


	//gamescene
	Object::Scene* gameScene = &world.scene.build(world);

	gameScene->add(world.rectangle.build(world, Object::Vector((world.width / 2.0) - 39, 0), 78, 42, c_displayColorGreen));

	auto topDisplay = &world.display.build(
		Object::TextRectangle(
			Object::Rectangle(world, Object::Vector((world.width / 2.0) - 5, 9), 10, 19, c_displayColorGreen), L"", c_displayFont),
		0);
	gameScene->add(*topDisplay);

	auto aTButton = &world.activatableTextButton.build(
		Object::ActivatableTButton(
			Object::TextRectangle(
				Object::Rectangle(world, Object::Vector(350, 50), 125, 28, c_buttonColorGreen),
				L"Active",
				c_buttonFontA
			),
			Object::TextRectangle(
				Object::Rectangle(world, Object::Vector(350, 50), 125, 28, c_buttonColorRedA),
				L"Inactive",
				c_buttonFontA
			),
			Time::AddToCounter<int>(topDisplay->counter(), 1),
			true
		)
	);
	gameScene->add(*aTButton);

	gameScene->add(world.button.build(Object::Button(
		Object::Rectangle(world, Object::Vector((world.width / 2.0) - 7, 45), 14, 8, c_buttonColorRedB),
		Time::ToggleATButton(*aTButton)
	)));


	//mainmenuscene
	Object::Scene* mainMenuScene = &world.scene.build(world);

	auto menuRect = &world.rectangle.build(world, Object::Vector((world.width * (3 / 8.0)), (world.height * (1/6.0))), world.width * (2/8.0), world.height * (4/7.0), c_mainMenuRectColor);
	mainMenuScene->add(*menuRect);

	const EngineName::Object::Rectangle buttonRectangle(
		world,
		Object::Vector(world.width * (7 / 16.0), world.height * (3 / 12.0)),
		world.width * (2 / 16.0),
		world.height * (1 / 16.0),
		c_startButtonColor);
	const EngineName::Time::ChangeActiveScene buttonAction(*gameScene);
	EngineName::Object::Button tempButton(buttonRectangle, buttonAction);
	EngineName::Object::TextButton tempTextButton(tempButton, L"Hello World", c_buttonFontB);
	auto button = &world.textButton.build(tempTextButton);
	mainMenuScene->add(*button);


	//set active scene
	world.setActiveScene(*mainMenuScene);
	Object::Complex::Bezier()
	//------------------------------------------------------
	return world.size();
}