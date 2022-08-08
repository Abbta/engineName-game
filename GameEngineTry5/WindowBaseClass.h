#include "framework.h"

#pragma once
#ifndef WINDOWBASECLASS_H
#define WINDOWBASECLASS_H
namespace EngineName
{
	namespace Base
	{
		/*
		* windowbaseclass class
		* used for clearer access to winapi window function
		* this was copied from a official guide on microsoft's own page and should not be edited, it will therefore not be commented and will be assumed to work as intended by the creator of it
		*/
		template <class DERIVED_TYPE>
		class WindowBaseClass
		{
		public:
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				DERIVED_TYPE* pThis = NULL;

				if (uMsg == WM_NCCREATE)
				{
					CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
					pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

					pThis->m_hwnd = hwnd;
				}
				else
				{
					pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
				}
				if (pThis)
				{
					return pThis->HandleMessage(uMsg, wParam, lParam);
				}
				else
				{
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}
			}

			WindowBaseClass() : m_hwnd(NULL) { }

			BOOL Create(
				PCWSTR lpWindowName,
				DWORD dwStyle,
				DWORD dwExStyle = 0,
				int x = CW_USEDEFAULT,
				int y = CW_USEDEFAULT,
				int nWidth = CW_USEDEFAULT,
				int nHeight = CW_USEDEFAULT,
				HWND hWndParent = 0,
				HMENU hMenu = 0
			)
			{
				WNDCLASS wc = { 0 };

				wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
				wc.hInstance = GetModuleHandle(NULL);
				wc.lpszClassName = ClassName();

				RegisterClass(&wc);

				m_hwnd = CreateWindowExW(
					dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
					nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
				);

				return (m_hwnd ? TRUE : FALSE);
			}

			HWND Window() const { return m_hwnd; }

		protected:

			virtual PCWSTR  ClassName() const = 0;
			virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

			HWND m_hwnd;
		};
	}
}
#endif