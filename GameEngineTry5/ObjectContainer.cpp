#include "ObjectContainer.h"
#include "Visible.h" //TEMPORARY
//#include "ObjectTasks.h"
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
			rectangle(this), circle(this), textRectangle(this), button(this), textButton(this),
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
		void ObjectContainer::drawVisible(const Object::Visible& visible) const
		{
			mpptr_window->mpptr_painter->mf_addToObjectsThatHasCalledDraw(visible);
		}

		//template<class T>
		void ObjectContainer::schedule(const Move& task, const int ms)
		{
			//assumes task is derived from class task
			//construct and store a new task
			Move &temp = mpc_theQueue.mpc_taskContainer.mpf_add(task);
			
			//add time to it
			temp.addTimeLeftInQueue(std::chrono::milliseconds(ms));

			//add a ref to it in the queue
			mpc_theQueue.mpf_addToQueue(temp);
			
		}
	}
}