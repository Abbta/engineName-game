#include "Button.h"
#include "ObjectContainer.h"
#include "OnClick.h"
namespace EngineName
{
	namespace Object
	{
		template<class T>
		Button::Button(const Rectangle& rect, const T& onClickTask)
			:Rectangle(rect), mp_actionRef(msp_getActionListener(mptr_world).addClickListener(Action::OnClick(mptr_world, onClickTask, this)))
		{
			//as button reuses task, it should not be destroyed
			mp_actionRef.mpptr_task->makeIndestructable();
		}

		template<class T>
		void Button::changeOnClickTask(const T& newTask)
		{
			mp_actionRef.mpf_changeTask(newTask);
			//as button reuses task, it should not be destroyed
			mp_actionRef.mpptr_task->makeIndestructable();
		}

		Action::ActionListener& Button::msp_getActionListener(Base::ObjectContainer* worldPtr)
		{
			return worldPtr->mp_actionListener;
		}

		void Button::mpf_changeOnClickArea(Visible& newArea)
		{
			mp_actionRef.mpf_changeArea(newArea);
		}
	}
}