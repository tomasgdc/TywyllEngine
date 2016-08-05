//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>

//OS Includes
#include "system\win32\win_local.h"
#include "System\sys_public.h"

//Engine Includes
#include "FrameWork\Engine.h"



LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{ //SWITCH START

	case WM_WINDOWPOSCHANGED:
	{
		RECT rect;
		if (::GetClientRect(hWnd, &rect))
		{
			if (rect.right > rect.left && rect.bottom > rect.top)
			{
				//glConfig.nativeScreenHeight = rect.right - rect.left;
				//glConfig.nativeScreenWidth = rect.bottom - rect.top;
			}
		}
	}
	break;
	case WM_MOVE:
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		Engine::getInstance().ShutDown();
		break;
	case WM_ACTIVATE:
	{
		// if we got here because of an alt-tab or maximize,
		// we should activate immediately.  If we are here because
		// the mouse was clicked on a title bar or drag control,
		// don't activate until the mouse button is released
		int	fActive, fMinimized;

		fActive = LOWORD(wParam);
		fMinimized = (BOOL)HIWORD(wParam);
		win32.activeApp = (fActive != WA_INACTIVE);
		if (win32.activeApp)
		{
			//LOAD FUCKING CUSTOM CURSOR
			//BULLSHIT -> NOT WORKING PROPERLY
			SetCursor(LoadCursor(nullptr, IDC_HAND));
		}

		if (fActive == WA_INACTIVE)
		{
			win32.movingWindow = false;
			if (Engine::getInstance().IsInitialized())
			{
				SetCursor(LoadCursor(nullptr, IDC_ARROW));
			}
		}
	}
		break;
	case WM_TIMER:
		break;
	case WM_SYSCOMMAND:
		break;
	case WM_SYSKEYDOWN:
		break;
	case WM_KEYDOWN:
	{
		int key = ((lParam >> 16) & 0xFF) | (((lParam >> 24) & 1) << 7);
		Sys_QueEvent(sysEventType_t::SE_KEY, key, true, 0, NULL, 0);
	}
		break;
	case WM_KEYUP:
	{
		int key = ((lParam >> 16) & 0xFF) | (((lParam >> 24) & 1) << 7);
		Sys_QueEvent(sysEventType_t::SE_KEY, key, false, 0, NULL, 0);
	}
		break;
	case WM_ENTERSIZEMOVE:
		win32.movingWindow = true;
		break;
	case WM_EXITSIZEMOVE:
	{
		win32.movingWindow = false;
		Sys_QueEvent(sysEventType_t::SE_RESIZED, win32.iCurrentHeight, win32.iCurrentWidth, 0, nullptr, 0);
	}
		break;
	case WM_SIZING:
	{
		WIN_Sizing(wParam, reinterpret_cast<RECT*>(lParam));
	}
		break;
	case WM_MOUSEMOVE:
	{
		//windowsx - less code -> thanks micrcosoft
		win32.bMouseOnWindows = true;
		win32.iMousePosX = GET_X_LPARAM(lParam);
		win32.iMousePosY = GET_Y_LPARAM(lParam);

		// Generate an event
		Sys_QueEvent(sysEventType_t::SE_MOUSE_ABSOLUTE, win32.iMousePosX, win32.iMousePosY, 0, nullptr, 0);

		// Get a mouse leave message
		TRACKMOUSEEVENT tme =
		{
			sizeof(TRACKMOUSEEVENT),
			TME_LEAVE,
			hWnd,
			0
		};
		TrackMouseEvent(&tme);
	}
		break;
	case WM_MOUSELEAVE:
		win32.bMouseOnWindows = false;
		Sys_QueEvent(sysEventType_t::SE_MOUSE_LEAVE, 0, 0, 0, nullptr, 0);
		break;
	case WM_LBUTTONDOWN:
		win32.mouseGrabbed = true;
		win32.mouseReleased = false;
		Sys_QueEvent(sysEventType_t::SE_KEY, 0, 1, 0, nullptr, 0);
		break;
	case WM_LBUTTONUP:
		win32.mouseGrabbed = false;
		win32.mouseReleased = true;
		Sys_QueEvent(sysEventType_t::SE_KEY, (int)keyNum_t::K_MOUSE1, 0, 0, nullptr, 0);
		break;
	case WM_RBUTTONDOWN:
		Sys_QueEvent(sysEventType_t::SE_KEY, (int)keyNum_t::K_MOUSE2, 1, 0, nullptr, 0);
		break;
	case WM_RBUTTONUP:
		Sys_QueEvent(sysEventType_t::SE_KEY, (int)keyNum_t::K_MOUSE2, 0, 0, nullptr, 0);
		break;
	case WM_MBUTTONDOWN:
		Sys_QueEvent(sysEventType_t::SE_KEY, (int)keyNum_t::K_MOUSE3, 1, 0, nullptr, 0);
		break;
	case WM_MBUTTONUP:
		Sys_QueEvent(sysEventType_t::SE_KEY, (int)keyNum_t::K_MOUSE3, 0, 0, nullptr, 0);
		break;
	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		int key = delta < 0 ? (int)keyNum_t::K_MWHEELDOWN : (int)keyNum_t::K_MWHEELUP;
		delta = abs(delta);
		while (delta-- > 0)
		{
			Sys_QueEvent(sysEventType_t::SE_KEY, key, true, 0, nullptr, 0);
			//Sys_QueEvent(sysEventType_t::SE_KEY, key, false, 0, nullptr, 0);
		}
		break;
	}
	
	}// SWITCH END
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void WIN_Sizing(WORD side, RECT *rect) 
{

	// restrict to a standard aspect ratio
	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;

	// Adjust width/height for window decoration
	RECT decoRect = { 0, 0, 0, 0 };
	AdjustWindowRect(&decoRect, WINDOW_STYLE | WS_SYSMENU, FALSE);
	int decoWidth = decoRect.right - decoRect.left;
	int decoHeight = decoRect.bottom - decoRect.top;

	width -= decoWidth;
	height -= decoHeight;
	
	win32.iCurrentHeight = height;
	win32.iCurrentWidth = width;
	glViewport(0, 0, width, height);

	//Sys_QueEvent(sysEventType_t::SE_RESIZED, height, width, 0, nullptr, 0);
}