#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywEngine\EventManager\IEventManager.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>


//Game Includes
#include "GameEvents.h"
#include "Game.h"
#include "GameLogic.h"
#include "MainView.h"
#include "Actors\ActorFactory.h"
#include "Actors\Actor.h"
#include "ScreenElementScene.h"
#include "Actors\RenderingComponent.h"

//Renderer Includes
#include <TywRenderer\GLRenderer.h>
#include <TywRenderer\Model.h>
#include <TywRenderer\SceneManager.h>

//Engine Includes
#include <TywEngine\FrameWork\Engine.h>
#include <TywEngine\EventManager\IEventManager.h>
#include <TywEngine\FrameWork\EngineSubsystems.h>
#include <TywEngine\EventManager\EventManagerImpl.h>
#include <TywEngine\EventManager\Events.h>
#include <TywEngine\LuaScripting\LuaStateManager.h>


Game::Game() :
	m_pGame(nullptr),
	m_ResCache(nullptr),
	m_bIsRunning(false),
	m_bIsEditorRunning(false),
	m_bQuitRequested(false),
	m_bQuitting(false),
	m_iColorDepth(32),
	m_HasModalDialog(0)
{
	//m_rcDesktop.bottom = m_rcDesktop.left = m_rcDesktop.right = m_rcDesktop.top = 0;
	//m_screenSize = Point(0, 0);
	//m_pNetworkEventForwarder = NULL;
	//m_pBaseSocketManager = NULL;
}


Game::~Game()
{
	SAFE_DELETE(m_pGame);
	SAFE_DELETE(m_ResCache);
}

BaseGameLogic * Game::VCreateGameAndView()
{
	m_pGame = TYW_NEW GameLogic;
	m_pGame->Init();

	std::shared_ptr<IGameView> menuView(TYW_NEW MainView(g_pRendGL));
	m_pGame->VAddView(menuView);

	return m_pGame;
}


bool Game::VLoadGame(void)
{
	return true;
}


bool Game::InitGame()
{


	// register all events
	VRegisterGameEvents();

	//
	// Initialize the ResCache - Chapter 5, page 141
	//
	//    Note - this is a little different from the book. Here we have a speccial resource ZIP file class, DevelopmentResourceZipFile,
	//    that actually reads directly from the source asset files, rather than the ZIP file. This is MUCH better during development, since
	//    you don't want to have to rebuild the ZIP file every time you make a minor change to an asset.
	//
	/*
	IResourceFile *zipFile = (m_bIsEditorRunning || m_Options.m_useDevelopmentDirectories) ?
		GCC_NEW DevelopmentResourceZipFile(L"Assets.zip", DevelopmentResourceZipFile::Editor) :
		GCC_NEW ResourceZipFile(L"Assets.zip");

	m_ResCache = GCC_NEW ResCache(50, zipFile);

	if (!m_ResCache->Init())
	{
		GCC_ERROR("Failed to initialize resource cache!  Are your paths set up correctly?");
		return false;
	}
	*/

	/*
	extern std::shared_ptr<IResourceLoader> CreateWAVResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateOGGResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateDDSResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateJPGResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateXmlResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateSdkMeshResourceLoader();
	extern std::shared_ptr<IResourceLoader> CreateScriptResourceLoader();
	*/

	// Note - register these in order from least specific to most specific! They get pushed onto a list.
	// RegisterLoader is discussed in Chapter 5, page 142

	/*
	m_ResCache->RegisterLoader(CreateWAVResourceLoader());
	m_ResCache->RegisterLoader(CreateOGGResourceLoader());
	m_ResCache->RegisterLoader(CreateDDSResourceLoader());
	m_ResCache->RegisterLoader(CreateJPGResourceLoader());
	m_ResCache->RegisterLoader(CreateXmlResourceLoader());
	m_ResCache->RegisterLoader(CreateSdkMeshResourceLoader());
	m_ResCache->RegisterLoader(CreateScriptResourceLoader());
	*/

	/*
	if (!LoadStrings("English"))
	{
		GCC_ERROR("Failed to load strings");
		return false;
	}
	*/


	//Initialize Lua Script Manager 
	if (!EngineSubsystems::getInstance().m_pLuaStateManager->VInit())
	{
		//Log error
		Engine::getInstance().Sys_Printf(stdout, "Could not load LUA");
		return false;
	}


	// Load the preinit file.  This is within braces to create a scope and destroy the resource once it's loaded.  We
	// don't need to do anything with it, we just need to load it.
	{
		//Resource resource(SCRIPT_PREINIT_FILE);
		//shared_ptr<ResHandle> pResourceHandle = m_ResCache->GetHandle(&resource);  // this actually loads the XML file from the zip file
	}

	// Register function exported from C++
	//ScriptExports::Register();
	//ScriptProcess::RegisterScriptClass();
	//BaseScriptComponent::RegisterScriptFunctions();


	//This could be done differently. Depending on players choice.
	//We could initialize specific renderer
	//For ex: If player choosed OpenGL -> Create new GLRenderer
	//If player choosed Vulkan -> Create new VulkanRenderer and so on
	g_pRendGL->VSetBackgroundColor(255, 20, 20, 200);
	g_pRendGL->VOnRestore();

	

	//In Game Code Complete 4 each Game View has a list of SceneNodes  but I think it's not right because due to duplicated data
	//My game view holds only orientation and position of player and renders ui specific to that game view. (still thinking about rendering in game view....)
	//Think about game view as a camera specific to each actor. :). Each actor will have it's own game view :)
	//Game view should only update it's positions and orientation in 3D world
	//Game view takes our current renderer
	m_pGame = VCreateGameAndView();
	if (!m_pGame)
	{
		return false;
	}

	// now that all the major systems are initialized, preload resources 
	//Preload calls are discussed in Chapter 5, page 148
	//m_ResCache->Preload("*.ogg", NULL);
	//m_ResCache->Preload("*.dds", NULL);
	//m_ResCache->Preload("*.jpg", NULL);




	std::shared_ptr<TestCube> testObject1(TYW_NEW TestCube("Cube", glx::vec3<float>(0.0f, 2.0f, 5.0f)));
	std::shared_ptr<TestCube> testObject2(TYW_NEW TestCube("Cube", glx::vec3<float>(5.0f, 2.0f, 5.0f)));
	std::shared_ptr<TestCube> testObject3(TYW_NEW TestCube("Cube", glx::vec3<float>(0.0f, 10.0f, 5.0f)));
	std::shared_ptr<TestCube> testObject4(TYW_NEW TestCube("Cube", glx::vec3<float>(-5.0f, 2.0f, 5.0f)));


	EngineSubsystems::getInstance().m_pSceneManager->AddChild(1, testObject1);
	EngineSubsystems::getInstance().m_pSceneManager->AddChild(2, testObject2);
	EngineSubsystems::getInstance().m_pSceneManager->AddChild(3, testObject3);
	EngineSubsystems::getInstance().m_pSceneManager->AddChild(4, testObject4);

	//Allocate memory
	EngineSubsystems::getInstance().m_pSceneManager->OnRestore();

	m_bIsRunning = true;
	return true;
}


void Game::VRegisterGameEvents(void)
{
	REGISTER_EVENT(EvtData_StartThrust);
	REGISTER_EVENT(EvtData_EndThrust);
	REGISTER_EVENT(EvtData_StartSteer);
	REGISTER_EVENT(EvtData_EndSteer);
}


void Game::OnFrameRender(double fTime,float fElapsedTime)
{
	BaseGameLogic * pGame = EngineSubsystems::getInstance().m_pGame->GetGameLogic();
	if (!pGame)
	{
		return;
	}

	//std::shared_ptr<IGameView>
	for (auto & iter: pGame->m_gameViews)
	{
			iter->VOnRender(fTime, fElapsedTime);	//Render UI
	}

	//Render Scene
	EngineSubsystems::getInstance().m_pSceneManager->OnRender();

	//Render Diagnostics
	pGame->VRenderDiagnostics();
}

void Game::OnUpdateGame(double fTime, float fElapsedTime)
{
	BaseGameLogic * pGame = EngineSubsystems::getInstance().m_pGame->GetGameLogic();
	if (!pGame)
	{
		return;
	}
	
	//EventManager::Get()->VUpdate(20); // allow event queue to process for up to 20 ms
	pGame->VOnUpdate(float(fTime), fElapsedTime);
}


void Game::HandleOSEvents(const struct sysEvent_t* pEvent)
{

}