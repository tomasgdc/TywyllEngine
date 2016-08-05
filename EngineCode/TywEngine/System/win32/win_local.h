//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once

//forward declaration
enum class sysEventType_t;


#define	WINDOW_STYLE	(WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE | WS_THICKFRAME)
void	Sys_QueEvent(sysEventType_t type, int value, int value2, int ptrLength, void *ptr, int inputDeviceNum);

void	Sys_PumpEvents(); // does window related events
void	Sys_Quit();		  // destroy windows

void	Sys_WAppendText(const wchar_t * msg); //sends appended text to win32 console
void	Sys_AppendText(const char* msg);

void	WIN_Sizing(WORD side, RECT *rect); //Re-calculates windows and viewport when windows resized

bool IsOnlyInstance(LPCTSTR gameTitle); //detects if it is the only instance
bool CheckStorage(const DWORDLONG diskSpaceNeeded); //Check storage
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded); //Check RAM and VRAM
DWORD ReadCPUSpeed(); //Get CPU speed;


// Main window procedure
LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// ====================================  WINDOWS INFORMATION =======================================================
struct Win32vars
{
	uint32_t			iDesktopWidth, iDesktopHeight;
	uint32_t			iCurrentWidth, iCurrentHeight;
	uint32_t			iMousePosX, iMousePosY;
	uint32_t			cdsFullscreen;	// 0 = not fullscreen, otherwise monitor numbe


	bool				bMouseOnWindows;			//is windows inside the windows or outside?
	bool				activeApp;					// changed with WM_ACTIVATE messages
	bool				mouseReleased;				// when the game has the console down or is doing a long operation
	bool				movingWindow;				// inhibit mouse grab when dragging the window
	bool				mouseGrabbed;				// current state of grab and hide
	bool				windowClassRegistered;
};

extern Win32vars win32;
// ================================================================================================
