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

		ObjectContainer::Width::Width(MainWindow& mainWindow) :
			mp_mainWinRef(mainWindow)
		{
			RECT temp;
			GetWindowRect(mp_mainWinRef.Window(), &temp);
			mp_width = temp.right - temp.left;
		}

		ObjectContainer::Width& ObjectContainer::Width::operator=(const unsigned int newWidth)
		{
			mp_width = newWidth;
			//recalculate
		}

		ObjectContainer::ObjectContainer() 
			:mpptr_window{ std::make_unique<MainWindow>(*this) }, window(&mpptr_window),
			rectangle(this), circle(this), textRectangle(this), mtemporary_origin(0,0), mpc_theQueue(),
			backgroundColor(*mpptr_window->mpptr_painter), width(*mpptr_window)
		{
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