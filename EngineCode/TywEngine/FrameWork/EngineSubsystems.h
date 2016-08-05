//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once
#include <Singleton.h>

//forward declaration
class Game;
class LuaStateManager;
class SceneManager;
class EventManager;

/*
Contains all engine subsystems
*/
class TYWENGINE_API EngineSubsystems: public Singleton<EngineSubsystems>
{
public:
	Game * m_pGame;
	LuaStateManager* m_pLuaStateManager;
	SceneManager*	 m_pSceneManager;
	EventManager*	 m_pEventManager;


public:
	EngineSubsystems();
	~EngineSubsystems();

	bool InitializeSubsystems();
	void ShutdownSubsystems();
private:
	bool m_bInitialized; //Indicates if all subsystems were initialized
	bool m_bDestroyed; //Indicates if subsystems were deleted already
};