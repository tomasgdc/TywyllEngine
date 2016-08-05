//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>

#include "FrameWork\Engine.h"
#include "System\sys_public.h"
#include "system\win32\win_local.h"


Win32vars win32;


/*
======================
Sys_PumpEvents
======================
*/
void Sys_PumpEvents() 
{
	MSG msg;

	while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		//If it gets WM_QUIT, do engine clean-up
		
		/*
		//This shit was decreasing perfomance and making stutters like crazy
		//Wow, who could knew that.... I gained more than 100 fps gain.
		if (GetMessage(&msg, nullptr, 0, 0) <= 0) {
			engine->Quit();
		}
		*/

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/*
======================
Sys_GenerateEvents
======================
*/
void Sys_GenerateEvents() 
{
	static bool entered = false;
	if (entered) 
	{
		return;
	}
	entered = true;

	//run message loop
	Sys_PumpEvents();

	entered = false;
}

/*
======================
Sys_Quit
======================
*/
void Sys_Quit() 
{
	//Sys_DestroyConsole();
	ExitProcess(0);
}

/*
============================
IsOnlyInstance
===========================
*/
bool IsOnlyInstance(LPCTSTR gameTitle) 
{
	// Find the window. If active, set and return false
	// Only one game instance may have this mutex at a time...
	HANDLE handle = CreateMutex(nullptr, TRUE, gameTitle);
	// Does anyone else think ‘ ERROR_SUCCESS’ is a bit of an oxymoron?
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, nullptr);
		if (hWnd)
		{
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

/*
============================
CheckStorage
===========================
*/
bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{

	return true;
}

/*
============================
CheckMemory
===========================
*/
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded)
	{
		// you don’t have enough physical memory. Tell the player to go get a real 
		// computer and give this one to his mother. 
		Engine::getInstance().Sys_Error(stdout, "CheckMemory Failure: Not enough physical memory.\r\n");
		return false;
	}

	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{
		// you don’t have enough virtual memory available. 
		// Tell the player to shut down the copy of Visual Studio running in the
		// background, or whatever seems to be sucking the memory dry.
		Engine::getInstance().Sys_Error(stderr, "CheckMemory Failure: Not enough virtual memory.\r\n");
		return false;
	}

	char *buff = new char[(unsigned int)virtualRAMNeeded];
	if (buff) {
		delete [] (buff);
	}
	else
	{
		// even though there is enough memory, it isn’t available in one 
		// block, which can be critical for games that manage their own memory
		Engine::getInstance().Sys_Error(stderr, "CheckMemory Failure: Not enough contiguous available memory.\r\n");
		return false;
	}
	return true;
}

/*
============================
ReadCPUSpeed
===========================
*/
DWORD ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		reinterpret_cast<LPCTSTR>("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		// query the key:
		RegQueryValueEx(hKey, reinterpret_cast<LPCTSTR>("~MHz"), NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}

#define	MAX_QUED_EVENTS		256
#define	MASK_QUED_EVENTS	( MAX_QUED_EVENTS - 1 )

sysEvent_t	eventQue[MAX_QUED_EVENTS];
int			eventHead = 0;
int			eventTail = 0;

/*
================
Sys_QueEvent

Ptr should either be null, or point to a block of data that can
be freed by the game later.
================
*/
void Sys_QueEvent(sysEventType_t type, int value, int value2, int ptrLength, void *ptr, int inputDeviceNum) {
	sysEvent_t * ev = &eventQue[eventHead & MASK_QUED_EVENTS];

	if (eventHead - eventTail >= MAX_QUED_EVENTS) 
	{
		Engine::getInstance().Sys_Printf(stdout, "Sys_QueEvent: overflow\r\n");
		// we are discarding an event, but don't leak memory
		delete(ev->evPtr);
		eventTail++;
	}
	eventHead++;

	ev->evType = type;
	ev->evValue = value;
	ev->evValue2 = value2;
	ev->evPtrLength = ptrLength;
	ev->evPtr = ptr;
	ev->inputDevice = inputDeviceNum;
}

/*
================
Sys_GetEvent
================
*/
sysEvent_t Sys_GetEvent() 
{
	sysEvent_t	ev;

	// return if we have data
	if (eventHead > eventTail) 
	{
		eventTail++;
		return eventQue[(eventTail - 1) & MASK_QUED_EVENTS];
	}

	// return the empty event 
	memset(&ev, 0, sizeof(ev));
	return ev;
}

/*
================
Sys_ClearEvents
================
*/
void Sys_ClearEvents() 
{
	eventHead = eventTail = 0;
}
