#include "ObjectContainer.h"
#include "Visible.h" //TEMPORARY
#include "ObjectTasks.h"
namespace EngineName
{
	using namespace Time;
	namespace Base
	{
		ObjectContainer::BackgroundColor::BackgroundColor(Drawing::Painter& painter):
			mp_painterref(painter), mp_color(Object::c_defaultBackgroundColor) {}

		ObjectContainer::BackgroundColor& ObjectContainer::BackgroundColor::operator=(const Object::Color& color)
		{
			mp_painterref.mf_changeBackgroundColor(color);
			mp_color = color;
			return *this;
		}

		ObjectContainer::ObjectContainer() 
			:mpptr_window{ std::make_unique<MainWindow>(*this) }, window(&mpptr_window),
			mtemporary_origin(0,0), mpc_theQueue(), nullVisible(this),
			rectangle(this), circle(this), textRectangle(this), 
			button(this), textButton(this), activatableTextButton(this),
			counter(this), display(this),
			objectGroup(this), scene(this),
			backgroundColor(*mpptr_window->mpptr_painter), width(*mpptr_window), height(*mpptr_window)
		{
			//reinitialise nullvisible and add it to allvisibles to give it a correct layerID
			mparr_allVisibles.push_back(nullptr);
			nullVisible = Object::NullVisible(this);
			mparr_allVisibles.back() = &nullVisible;
		}

		//returns the amount of user added objects
		int ObjectContainer::size()
		{
			return static_cast<int>(mparr_allVisibles.size());
		}

		//requests drawing for that visible
		bool ObjectContainer::drawVisible(const Object::Visible& visible) const
		{
			const auto activeScene = mpptr_window->mpptr_painter->mf_getActiveScene();
			//if it is in active scene
			if (activeScene == nullptr
				|| activeScene->contains(visible))
			{
				//draw
				mpptr_window->mpptr_painter->mf_addToObjectsThatHasCalledDraw(visible);
				//return that it was drawn
				return true;
			}
			else
			{
				//if not in active scene
				//return request denied
				return false;
			}
		}

		void ObjectContainer::setActiveScene(Object::Scene& scene)
		{
			Drawing::Painter& painterRef = *mpptr_window->mpptr_painter;
			painterRef.mf_clearWindow();
			painterRef.mf_changeActiveScene(scene.mf_getVisibles());
			painterRef.mf_drawAll();
		}
	}
}