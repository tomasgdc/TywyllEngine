//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>

//Engine Includes
#include "EngineSubsystems.h"
#include "EventManager\Events.h"
#include "EventManager\EventManagerImpl.h"
#include "FrameWork\Engine.h"
#include "System\win32\win_local.h"
#include "LuaScripting\LuaStateManager.h"

//Renderer Includes
#include <TywRenderer\IRenderer.h>
#include <TywRenderer\SceneManager.h>


//Game Includes
#include <TywGame\Game.h>



EngineSubsystems::EngineSubsystems() :
	m_pLuaStateManager(nullptr),
	m_pGame(nullptr),
	m_pSceneManager(nullptr),
	m_pEventManager(nullptr),
	m_bInitialized(false),
	m_bDestroyed(false)
{

}

EngineSubsystems::~EngineSubsystems()
{
	//If subsystems were not destroyed. Destroy now.
	if (!m_bDestroyed)
	{
		ShutdownSubsystems();
	}
}

bool EngineSubsystems::InitializeSubsystems()
{	
	if (!m_bInitialized)
	{
		//Create objects
		m_pEventManager = TYW_NEW EventManager;
		m_pLuaStateManager = TYW_NEW LuaStateManager;
		m_pSceneManager = TYW_NEW SceneManager;
		m_pGame = TYW_NEW Game;

		//Call each object initialization functions
	    if(!m_pLuaStateManager->VInit())return false;
		if(!m_pGame->InitGame())return false;
		
		m_bInitialized = true;
	}
	return true;
}


void EngineSubsystems::ShutdownSubsystems()
{
	if (!m_bDestroyed)
	{
		SAFE_DELETE(m_pGame);
		SAFE_DELETE(m_pSceneManager);
		SAFE_DELETE(m_pLuaStateManager)
		SAFE_DELETE(m_pEventManager);
		m_bDestroyed = true;
	}
		
}


