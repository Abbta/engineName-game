#include "MainWindow.h"
#include "Painter.h"
#include "ObjectContainer.h"
#include <Windowsx.h>
/*
* TODO WHEN NEEDED:
*	add seperate files to all large functions such as handlemessage
*/
namespace EngineName
{
	namespace Base
	{
		/*
		* handlemessage function
		* is a member of mainwindow class
		* is called as often as possible by winapi
		* the parameters contain input from the OS
		*	uMsg is a broadcasted windows message (for example left mouse button has been pressed)
		*	wParam and lParam may contain additional information about the message (for example the coordinates of the cursor)
		* will call a function for painting
		* will call relevant objects onInput() functions if the user provides input
		*/
		LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_CREATE:
				//make painter construct graphics resources
				mpptr_painter->mf_createGraphicsResources();
				mpptr_painter->mf_clearWindow();
				return 0;
			case WM_SIZE:
				//resize
				return 0;
			case WM_LBUTTONDOWN:
				//tell engine a click has happened and where in engine coordinates
				mp_world.mp_actionListener.click(
					mp_world.width.fromInputWidth(GET_X_LPARAM(lParam)),
					mp_world.width.fromInputWidth(GET_Y_LPARAM(lParam)));
				return 0;
			case WM_DESTROY:
				//close down main window
				PostQuitMessage(0);
				return 0;
			default:
				//no specific calls from api

				//execute scheduled tasks or update the queue timer
				mp_world.mpc_theQueue.mpf_update(mp_world);

				//draw objects which need repainting
				mpptr_painter->mf_refresh();
				//neccessary return
				return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
			}
		}

		/*
		* How time flow will work:
		*	There is a task base object
		*	From these there are engine derived tasks (such as change coordinates)
		*	The dev can also derive their own task objects which of course can have multiple other tasks in them
		*	These can via a task object member function be put in The Queue
		*	A function which will either be called after each handle message or constantly in a separate thread will:
		*		tell all tasks how much longer they need to remain in The Queue
		*		Put things that have waited for too long in a to-do list
		*   If the to-do list has tasks on it, these will be executed via their respective task object member function
		*/

		/*
		How drawing system will work:
			After each handlemessage loop it calls a draw function if a conditional is set
			Conditonal can be set by the following:
				Every visible has a .draw()
					calls a Draw object which does the drawing
				World has a Draw object
					has .drawAll()
					has a vector with all objects visible on screen
						as they were when last drawn
					has a function that takes an object and returns a vector with all objects that overlapps 
					contains the draw funtion
						is called from handlemessage
					contains conditional and what objects to be drawn
					also contains brushes and shapes
		*/
	}
}