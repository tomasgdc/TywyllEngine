//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>


//OS Includes
#include "System\sys_public.h"


//Engine Includes
#include "EventManager\Events.h"
#include "EventManager\EventManagerImpl.h"
#include "FrameWork\Engine.h"
#include "System\win32\win_local.h"
#include "LuaScripting\LuaStateManager.h"
#include "EngineSubsystems.h"

//Renderer Includes
#include <TywRenderer\GLRenderer.h>
#include <TywRenderer\SceneManager.h>


//Game Includes
#include <TywGame\Game.h>




Engine::Engine():
	m_bIsRunning(false),
	m_bIsSysConsoleRunning(false),
	m_bFullyInitialized(false),
	m_iCountNumGameFrames(0),
	m_iTime_backend(0),
	m_iTime_frontend(0),
	m_iTime_gameDraw(0),
	m_iTime_gameFrame(0),
	m_iTime_gpu(0),
	m_iTime_maxGameFrame(0),
	m_iTime_shadows(0)
{
}

void Me(IEventDataPtr)
{
	fprintf(stdout, "hi \n");
}

void Engine::Init(int argc, const char * const * argv, const char *cmdline, int windowWidth, int windowHeight)
{
	
//Enable memory leak detection
#if defined (_DEBUG) || defined (DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
	
	//Set windows size
	win32.iCurrentHeight = windowHeight;
	win32.iCurrentWidth = windowWidth;

	//Initialize Renderer
	if (!g_pRendGL->VInitRenderer(win32.iCurrentHeight, win32.iCurrentWidth, false, MainWndProc)){
		return;
	}


	//Initialize all other subsystems
	if (!EngineSubsystems::getInstance().InitializeSubsystems()) {
		return;
	}
	m_bFullyInitialized = true;
}





bool Engine::IsInitialized() const 
{
	return m_bFullyInitialized;
}

void Engine::ShutDown() 
{
	//Shutdown engine subsystems
	EngineSubsystems::getInstance().ShutdownSubsystems();


	Engine::getInstance().Sys_WDebugPrintf(L"renderSystem->shutdown \n");
	//renderSystem->Shutdown();

	Engine::getInstance().Sys_WDebugPrintf(L"system->shutdow \n");
	Sys_Quit();


	//Shutdown Renderer
	m_pRenderer->VShutdown();


	//_CRTDBG_LEAK_CHECK_DF is used at program initialization
	// to force a leak check just before program exit. This
	// is important because some classes may dynamically
	// allocate memory in globally constructed objects.
	//
	_CrtDumpMemoryLeaks(); // Reports leaks to stderr
	// Destroy the logging system at the last possible moment
}




bool Engine::ProcessOSEvent(struct sysEvent_t *event)
{
	if (event->evType == sysEventType_t::SE_KEY)
	{

	}
	else if (event->evType == sysEventType_t::SE_RESIZED)
	{
	
	}
	else if (event->evType == sysEventType_t::SE_MOUSE_ABSOLUTE)
	{
		//fprintf(stdout, "Mouse x %i, mouse y %i \n", event->evValue, event->evValue2);
	}

	SAFE_DELETE(event->evPtr)
	return true;
}

bool Engine::RunOSEvents()
{
	sysEvent_t	ev;


	while (1)
	{
		ev  = Sys_GetEvent();

		if (ev.evType == sysEventType_t::SE_NONE)
		{
			return true;
		}

		Engine::ProcessOSEvent(&ev);
	}

	//No events to process
	return false;
}