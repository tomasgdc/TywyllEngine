#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>


//Engine Includes
#include <TywEngine\EventManager\IEventManager.h>
#include <TywEngine\FrameWork\EngineSubsystems.h>
#include <TywEngine\EventManager\EventManagerImpl.h>
#include <TywEngine\EventManager\Events.h>


//Game Includes
#include "BaseGameLogic.h"
#include "MainView.h"
#include "GameOptions.h"
#include "BaseGameLogic.h"

//Renderer Includes
#include <TywRenderer\IRenderer.h>
#include <TywRenderer\SceneNode.h>


MainView::MainView(IRenderer* pRenderer): HumanView(pRenderer)
{
	m_bShowUI = true;
	RegisterAllDelegates();
}


MainView::~MainView()
{
	RemoveAllDelegates();
}

LRESULT CALLBACK MainView::VOnMsgProc(AppMsg msg)
{
	if (HumanView::VOnMsgProc(msg))
		return 1;

	if (msg.m_uMsg == WM_KEYDOWN)
	{
		if (msg.m_wParam == VK_F1)
		{
			m_bShowUI = !m_bShowUI;
			//m_StandardHUD->VSetVisible(m_bShowUI);
			return 1;
		}
		else if (msg.m_wParam == VK_F2)
		{
			// test the picking API

			POINT ptCursor;
			GetCursorPos(&ptCursor);
			//ScreenToClient(g_pApp->GetHwnd(), &ptCursor);

			//RayCast rayCast(ptCursor);
			//m_pScene->Pick(&rayCast);
			//rayCast.Sort();

			//if (rayCast.m_NumIntersections)
			//{
				//// You can iterate through the intersections on the raycast.
				//int a = 0;
			//}
		}
		else if (msg.m_wParam == VK_F3)
		{
			//extern void CreateThreads();
			//CreateThreads();

			//extern void testThreading(ProcessManager *procMgr, bool runProtected);
			//testThreading(m_pProcessManager, true);

			//return 1;

			//Sleep(5000);
			//testThreading(m_pProcessManager, false);
			//Sleep(5000);

			//extern void testRealtimeEvents(ProcessManager *procMgr);
			//testRealtimeEvents(m_pProcessManager);

			//extern void testRealtimeDecompression(ProcessManager *procMgr);
			//testRealtimeDecompression(m_pProcessManager);
		}
		else if (msg.m_wParam == VK_F4)
		{
			//Resource resource("scripts\\test.lua");
			//shared_ptr<ResHandle> pResourceHandle = g_pApp->m_ResCache->GetHandle(&resource);  // this actually loads the Lua file from the zip file
		}
		else if (msg.m_wParam == VK_F5)
		{
			//shared_ptr<EvtData_ScriptEventTest_ToLua> pEvent(GCC_NEW EvtData_ScriptEventTest_ToLua);
			//IEventManager::Get()->VQueueEvent(pEvent);
		}
		else if (msg.m_wParam == VK_F6)
		{
			//LuaStateManager::Get()->VExecuteString("TestProcess()");
		}
		else if (msg.m_wParam == VK_F8)
		{
			//TeapotWarsLogic *twg = static_cast<TeapotWarsLogic *>(g_pApp->m_pGame);
			//twg->ToggleRenderDiagnostics();

		}
		else if (msg.m_wParam == VK_F9)
		{
			//m_KeyboardHandler = m_pTeapotController;
			//m_PointerHandler = m_pTeapotController;
			//m_pCamera->SetTarget(m_pTeapot);
			//m_pTeapot->SetAlpha(0.8f);
			//ReleaseCapture();
			return 1;
		}
		else if (msg.m_wParam == VK_F11)
		{
			//m_KeyboardHandler = m_pFreeCameraController;
			//m_PointerHandler = m_pFreeCameraController;
			//m_pCamera->ClearTarget();
			////m_pTeapot->SetAlpha(fOPAQUE);
			//SetCapture(g_pApp->GetHwnd());
			return 1;
		}
		else if (msg.m_wParam == 'Q' || msg.m_wParam == VK_ESCAPE)				// Jan 2010 - mlm - added VK_ESCAPE since it is on the onscreen help!
		{
			//if (MessageBox::Ask(QUESTION_QUIT_GAME) == IDYES)
			//{
			//	g_pApp->SetQuitting(true);
			//}
			return 1;
		}
	}
	return 0;
}



void MainView::VRenderText()
{
	if (!m_gameplayText.empty())
	{
		//D3DRenderer::g_pTextHelper->SetInsertionPos(g_pApp->GetScreenSize().x / 2, 5);
		//D3DRenderer::g_pTextHelper->SetForegroundColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		//D3DRenderer::g_pTextHelper->DrawTextLine(m_gameplayText.c_str());
		//D3DRenderer::g_pTextHelper->SetInsertionPos(g_pApp->GetScreenSize().x / 2 - 1, 5 - 1);
		//D3DRenderer::g_pTextHelper->SetForegroundColor(D3DXCOLOR(0.25f, 1.0f, 0.25f, 1.0f));
		//D3DRenderer::g_pTextHelper->DrawTextLine(m_gameplayText.c_str());
	}
	if (m_bShowUI)
	{
		//Game State...
		switch (m_BaseGameState)
		{
		case BaseGameState::BGS_Initializing:
			//D3DRenderer::g_pTextHelper->DrawTextLine(g_pApp->GetString(_T("IDS_INITIALIZING")).c_str());
			break;

		case BaseGameState::BGS_MainMenu:
			//D3DRenderer::g_pTextHelper->DrawTextLine(L"Main Menu");
			break;

			//			case BGS_SpawnAI:
			//				D3DRenderer::g_pTextHelper->DrawTextLine(L"Spawn AI");
			//				break;

		case BaseGameState::BGS_WaitingForPlayers:
			//D3DRenderer::g_pTextHelper->DrawTextLine(g_pApp->GetString(_T("IDS_WAITING")).c_str());
			break;

		case BaseGameState::BGS_LoadingGameEnvironment:
			//D3DRenderer::g_pTextHelper->DrawTextLine(g_pApp->GetString(_T("IDS_LOADING")).c_str());
			break;

		case BaseGameState::BGS_Running:
			//D3DRenderer::g_pTextHelper->DrawTextLine(g_pApp->GetString(_T("IDS_RUNNING")).c_str());
			//D3DRenderer::g_pTextHelper->DrawTextLine(g_pApp->GetString(_T("IDS_NOPHYSICS")).c_str());
			break;
		}
		//Camera...
		TCHAR buffer[256];
		const TCHAR *s = NULL;
		glx::mat4<float> toWorld;
		glx::mat4<float> fromWorld;
		if (m_pCamera)
		{
			m_pCamera->VGet()->Transform(&toWorld, &fromWorld);
		}

		//swprintf(buffer, g_pApp->GetString(_T("IDS_CAMERA_LOCATION")).c_str(), toWorld.m[3][0], toWorld.m[3][1], toWorld.m[3][2]);
		//D3DRenderer::g_pTextHelper->DrawTextLine(buffer);
		//...Camera

		//Help text.  Right justified, lower right of screen.
		//RECT helpRect;
		//helpRect.left = 0;
		//helpRect.right = g_pApp->GetScreenSize().x - 10;
		//helpRect.top = g_pApp->GetScreenSize().y - 15 * 8;
		//helpRect.bottom = g_pApp->GetScreenSize().y;
		//D3DRenderer::g_pTextHelper->SetInsertionPos(helpRect.right, helpRect.top);
		//D3DRenderer::g_pTextHelper->SetForegroundColor(D3DXCOLOR(1.0f, 0.75f, 0.0f, 1.0f));
		//D3DRenderer::g_pTextHelper->DrawTextLine(helpRect, DT_RIGHT, g_pApp->GetString(_T("IDS_CONTROLS_HEADER")).c_str());
		//helpRect.top = g_pApp->GetScreenSize().y - 15 * 7;
		//D3DRenderer::g_pTextHelper->DrawTextLine(helpRect, DT_RIGHT, g_pApp->GetString(_T("IDS_CONTROLS")).c_str());
		//...Help
	}//end if (m_bShowUI)

	//D3DRenderer::g_pTextHelper->End();
}



void MainView::VOnUpdate(unsigned long deltaMs)
{
	HumanView::VOnUpdate(deltaMs);

	//if (m_pFreeCameraController)
	//{
	//	m_pFreeCameraController->OnUpdate(deltaMs);
	//}

	//if (m_pTeapotController)
	//{
	//	m_pTeapotController->OnUpdate(deltaMs);
	//}

	//Send out a tick to listeners.
	//shared_ptr<EvtData_Update_Tick> pTickEvent(GCC_NEW EvtData_Update_Tick(deltaMs));
	//IEventManager::Get()->VTriggerEvent(pTickEvent);
}


void MainView::VOnAttach(unsigned int vid, unsigned int aid)
{
	HumanView::VOnAttach(vid, aid);
}

void MainView::VSetControlledActor(unsigned int actorId)
{
	//m_pTeapot = static_pointer_cast<SceneNode>(m_pScene->FindActor(actorId));
	//if (!m_pTeapot)
	//{
	//	GCC_ERROR("Invalid teapot");
	//	return;
	//}

	HumanView::VSetControlledActor(actorId);

	//m_pTeapotController.reset(GCC_NEW TeapotController(m_pTeapot));
	//m_KeyboardHandler = m_pTeapotController;
	//m_PointerHandler = m_pTeapotController;
	//m_pCamera->SetTarget(m_pTeapot);
	//m_pTeapot->SetAlpha(0.8f);
}


bool MainView::VLoadGameDelegate(tinyxml2::XMLElement* pLevelData)
{
	if (!HumanView::VLoadGameDelegate(pLevelData))
		return false;

	//m_StandardHUD.reset(GCC_NEW StandardHUD);
	//VPushElement(m_StandardHUD);

	// A movement controller is going to control the camera, 
	// but it could be constructed with any of the objects you see in this
	// function. You can have your very own remote controlled sphere. What fun...
	//m_pFreeCameraController.reset(GCC_NEW MovementController(m_pCamera, 0, 0, false));

	//m_pScene->VOnRestore();
	return true;
}

// event delegates
void MainView::GameplayUiUpdateDelegate(IEventDataPtr pEventData)
{
	//shared_ptr<EvtData_Gameplay_UI_Update> pCastEventData = static_pointer_cast<EvtData_Gameplay_UI_Update>(pEventData);
	//if (!pCastEventData->GetUiString().empty())
		//m_gameplayText = s2ws(pCastEventData->GetUiString());
	//else
		//m_gameplayText.clear();
}

void MainView::SetControlledActorDelegate(IEventDataPtr pEventData)
{
	//shared_ptr<EvtData_Set_Controlled_Actor> pCastEventData = static_pointer_cast<EvtData_Set_Controlled_Actor>(pEventData);
	//VSetControlledActor(pCastEventData->GetActorId());
}

void MainView::RegisterAllDelegates(void)
{

	//IEventManager* pGlobalEventManager = IEventManager::Get();
	//pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsHumanView::GameplayUiUpdateDelegate), EvtData_Gameplay_UI_Update::sk_EventType);
	//pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsHumanView::SetControlledActorDelegate), EvtData_Set_Controlled_Actor::sk_EventType);
}

void MainView::RemoveAllDelegates(void)
{
	//IEventManager* pGlobalEventManager = IEventManager::Get();
	//pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsHumanView::GameplayUiUpdateDelegate), EvtData_Gameplay_UI_Update::sk_EventType);
	//pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsHumanView::SetControlledActorDelegate), EvtData_Set_Controlled_Actor::sk_EventType);
}
