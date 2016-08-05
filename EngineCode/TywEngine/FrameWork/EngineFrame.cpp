//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>

//OS Includes
#include "System\sys_public.h"
#include "System\win32\win_local.h"

//Engine Includes
#include "EngineSubsystems.h"
#include "EventManager\Events.h"
#include "EventManager\EventManagerImpl.h"
#include "FrameWork\Engine.h"

#include "LuaScripting\LuaStateManager.h"
#include "FrameWork\EngineSubsystems.h"

//Renderer Includes
#include <TywRenderer\GLRenderer.h>
#include <TywRenderer\SceneManager.h>
#include <TywRenderer\RenderProgs.h>


//Game Includes
#include <TywGame\Game.h>






void GameThread::Run(){
	//Engine::getInstance().m_rameTiming.startGameTime = Sys_Microseconds();
	
	// debugging tool to test frame dropping behavior
	//Not implemented

	if (numGameFrames == 0) {
		// Ensure there's no stale gameReturn data from a paused game
		//Not implemented
	}

	//run game logic
	//gApp->Update();
	//Engine::getInstance().frameTiming.finishGameTime = Sys_Microseconds();

	//SetThreadGameTime((Engine::getInstance().frameTiming.finishGameTime - Engine::getInstance().frameTiming.startGameTime) / 1000);
	
	// build render commands and geometry
	//engine_local.Draw();

//	Engine::getInstance().frameTiming.finishDrawTime = Sys_Microseconds();

//	SetThreadRenderTime((Engine::getInstance().frameTiming.finishDrawTime - Engine::getInstance().frameTiming.finishGameTime) / 1000);

//	SetThreadTotalTime((Engine::getInstance().frameTiming.finishDrawTime - Engine::getInstance().frameTiming.startGameTime) / 1000);
}


void GameThread::RunGameAndDraw(int numGameFrames_, int startGameFrame) {
	//wait for thread
	//Not implemented


	// save the usercmds for the background thread to pick up
	//Not implemented

	// grab the return value created by the last thread execution
	//Not implemented

	numGameFrames = numGameFrames_;

	// start the thread going -> run game and draw in seperate threads
	//Not implemented
	{
		Run();
	}

	//return the latched result while the thread runs in the background
	//Not implemented
}

void Engine::Draw() {

	//draw game, console and other things
	//Not all things implemented


	//gApp->Render();
}


void Engine::Frame() 
{
	static uint64_t g_GameFrames = 0;
	auto frameTimeStart = std::chrono::high_resolution_clock::now();
	
	//pump all windows events
	Sys_GenerateEvents();
	Engine::RunOSEvents();


	//Start Frame
	g_pRendGL->StartFrame();


	renderProgManager.UseProgram("geo.glsl");
	Game::OnUpdateGame(0, 0);
	Game::OnFrameRender(0, 0);

	auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - frameTimeStart);


	ImGui_ImplGlfwGL3_NewFrame(frameTime.count(), win32);
	ImguiRender();


	//Finish Frame
	g_pRendGL->EndFrame(&m_iTime_gpu);
}