#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>

//Engine Includes
#include <TywEngine\EventManager\IEventManager.h>


//Game Includes
#include "GameLogic.h"
#include "HumanView.h"
#include "ScreenElementScene.h"
#include "Actors\ActorFactory.h"
#include "Actors\Actor.h"
#include "Actors\TransformComponent.h"
#include "Actors\RenderingComponent.h"

//Renderer Includes
#include <TywRenderer\IRenderer.h>
#include <TywRenderer\Model.h>





GameLogic::GameLogic()
{
	//m_pPhysics.reset(CreateGamePhysics());
	RegisterAllDelegates();
}


//
// TeapotWarsLogic::~TeapotWarsLogic
//
GameLogic::~GameLogic()
{
	RemoveAllDelegates();
	DestroyAllNetworkEventForwarders();
}


void GameLogic::VSetProxy()
{
	// FUTURE WORK: This can go in the base game logic!!!!
	BaseGameLogic::VSetProxy();
}


/*
class WatchMeProcess : public Process
{
	ActorId m_me;
	ActorId m_target;
public:
	WatchMeProcess(ActorId me, ActorId target) { m_me = me; m_target = target; }
	void VOnUpdate(unsigned long deltaMs);
};
*/

/*
void WatchMeProcess::VOnUpdate(unsigned long deltaMs)
{
	StrongActorPtr pTarget = MakeStrongPtr(g_pApp->m_pGame->VGetActor(m_target));
	StrongActorPtr pMe = MakeStrongPtr(g_pApp->m_pGame->VGetActor(m_me));

	std::shared_ptr<TransformComponent> pTargetTransform = MakeStrongPtr(pTarget->GetComponent<TransformComponent>(TransformComponent::g_Name));
	std::shared_ptr<TransformComponent> pMyTransform = MakeStrongPtr(pMe->GetComponent<TransformComponent>(TransformComponent::g_Name));

	if (!pTarget || !pMe || !pTargetTransform || !pMyTransform)
	{
		//GCC_ERROR("This shouldn't happen");
		//Fail();
	}

	glx::vec3<float> targetPos = pTargetTransform->GetPosition();
	glx::mat4<float> myTransform = pMyTransform->GetTransform();
	glx::vec3<float> myDir = myTransform.GetDirection();
	myDir = glx::vec3<float>(0.0f, 0.0f, 1.0f);
	glx::vec3<float> myPos = pMyTransform->GetPosition();

	glx::vec3<float> toTarget = targetPos - myPos;
	GLXVec3Normalize(&toTarget);


	
	float dotProduct = GLXVec3Dot(&myDir, &toTarget);

	glx::vec3<float> crossProduct;
	GLXVec3Cross(&crossProduct, &myDir, &toTarget);

	float angleInRadians = acos(dotProduct);

	if (crossProduct.y < 0)
		angleInRadians = -angleInRadians;

	glx::mat4<float> rotation;
	GLXMatrixRotationY(&rotation, angleInRadians);
	rotation.SetPosition(myPos);
	pMyTransform->SetTransform(rotation);
}
*/


//
// TeapotWarsLogic::VChangeState
//
void GameLogic::VChangeState(BaseGameState newState)
{
	BaseGameLogic::VChangeState(newState);

	switch (newState)
	{
	case BaseGameState::BGS_WaitingForPlayers:
	{

		// spawn all local players (should only be one, though we might support more in the future)
		//GCC_ASSERT(m_ExpectedPlayers == 1);
		for (int i = 0; i < m_ExpectedPlayers; ++i)
		{
			//std::shared_ptr<IGameView> playersView(TYW_NEW  TeapotWarsHumanView(g_pApp->m_Renderer));
			//VAddView(playersView);

			if (m_bProxy)
			{
				// if we are a remote player, all we have to do is spawn our view - the server will do the rest.
				return;
			}
		}

		// spawn all remote player's views on the game
		for (int i = 0; i < m_ExpectedRemotePlayers; ++i)
		{
			//std::shared_ptr<IGameView> remoteGameView(GCC_NEW NetworkGameView);
			//VAddView(remoteGameView);
		}

		// spawn all AI's views on the game
		for (int i = 0; i < m_ExpectedAI; ++i)
		{
			//std::shared_ptr<IGameView> aiView(GCC_NEW AITeapotView(m_pPathingGraph));
			//VAddView(aiView);
		}
		break;
	}


	case BaseGameState::BGS_SpawningPlayersActors:
	{
		if (m_bProxy)
		{
			// only the server needs to do this.
			return;
		}

		for (auto it = m_gameViews.begin(); it != m_gameViews.end(); ++it)
		{
			std::shared_ptr<IGameView> pView = *it;
			if (pView->VGetType() == GameView_Human)
			{
				StrongActorPtr pActor = VCreateActor("actors\\player_teapot.xml", NULL);
				if (pActor)
				{
					//std::shared_ptr<EvtData_New_Actor> pNewActorEvent(GCC_NEW EvtData_New_Actor(pActor->GetId(), pView->VGetId()));
					//IEventManager::Get()->VTriggerEvent(pNewActorEvent);  // [rez] This needs to happen asap because the constructor function for Lua (which is called in through VCreateActor()) queues an event that expects this event to have been handled
				}
			}
			else if (pView->VGetType() == GameView_Remote)
			{
				//std::shared_ptr<NetworkGameView> pNetworkGameView = static_pointer_cast<NetworkGameView, IGameView>(pView);
				StrongActorPtr pActor = VCreateActor("actors\\remote_teapot.xml", NULL);
				if (pActor)
				{
					//std::shared_ptr<EvtData_New_Actor> pNewActorEvent(GCC_NEW EvtData_New_Actor(pActor->GetId(), pNetworkGameView->VGetId()));
					//IEventManager::Get()->VQueueEvent(pNewActorEvent);
				}
			}
			else if (pView->VGetType() == GameView_AI)
			{
				//std::shared_ptr<AITeapotView> pAiView = static_pointer_cast<AITeapotView, IGameView>(pView);
				StrongActorPtr pActor = VCreateActor("actors\\ai_teapot.xml", NULL);
				if (pActor)
				{
					//std::shared_ptr<EvtData_New_Actor> pNewActorEvent(GCC_NEW EvtData_New_Actor(pActor->GetId(), pAiView->VGetId()));
					//IEventManager::Get()->VQueueEvent(pNewActorEvent);
				}
			}
		}

		break;
	}
	}
}

//
// TeapotWarsLogic::VAddView
//
void GameLogic::VAddView(std::shared_ptr<IGameView> pView, unsigned int actor)
{
	BaseGameLogic::VAddView(pView, actor);
	//  This is commented out because while the view is created and waiting, the player has NOT attached yet. 
	//	if (dynamic_pointer_cast<NetworkGameView>(pView))
	//	{
	//		m_HumanPlayersAttached++;
	//	}

	/*
	if (std::dynamic_pointer_cast<TeapotWarsHumanView>(pView))
	{
		m_HumanPlayersAttached++;
	}
	else if (std::dynamic_pointer_cast<AITeapotView>(pView))
	{
		m_AIPlayersAttached++;
	}
	*/
}


void GameLogic::VMoveActor(const unsigned int id, glx::mat4<float> const &mat)
{
	BaseGameLogic::VMoveActor(id, mat);

	// [rez] HACK: This will be removed whenever the gameplay update stuff is in.  This is meant to model the death
	// zone under the grid.

	// FUTURE WORK - This would make a great basis for a Trigger actor that ran a LUA script when other
	//               actors entered or left it!

	StrongActorPtr pActor = MakeStrongPtr(VGetActor(id));
	if (pActor)
	{
		std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
		if (pTransformComponent && pTransformComponent->GetPosition().y < -25)
		{
			//std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorEvent(GCC_NEW EvtData_Destroy_Actor(id));
			//IEventManager::Get()->VQueueEvent(pDestroyActorEvent);
		}
	}
}

void GameLogic::RequestStartGameDelegate(IEventDataPtr pEventData)
{
	VChangeState(BaseGameState::BGS_WaitingForPlayers);
}

void GameLogic::EnvironmentLoadedDelegate(IEventDataPtr pEventData)
{
	++m_HumanGamesLoaded;
}


// FUTURE WORK - this isn't TeapotWars specific so it can go into the game agnostic base class
void GameLogic::RemoteClientDelegate(IEventDataPtr pEventData)
{
	// This event is always sent from clients to the game server.

	//std::shared_ptr<EvtData_Remote_Client> pCastEventData = static_pointer_cast<EvtData_Remote_Client>(pEventData);
	//const int sockID = pCastEventData->GetSocketId();
	//const int ipAddress = pCastEventData->GetIpAddress();

	// go find a NetworkGameView that doesn't have a socket ID, and attach this client to that view.
	for (auto it = m_gameViews.begin(); it != m_gameViews.end(); ++it)
	{
		std::shared_ptr<IGameView> pView = *it;
		if (pView->VGetType() == GameView_Remote)
		{
			//std::shared_ptr<NetworkGameView> pNetworkGameView = static_pointer_cast<NetworkGameView, IGameView>(pView);
			//if (!pNetworkGameView->HasRemotePlayerAttached())
			//{
			//	pNetworkGameView->AttachRemotePlayer(sockID);
			//	CreateNetworkEventForwarder(sockID);
			//	m_HumanPlayersAttached++;

	//			return;
		//	}
		}
	}

}

void GameLogic::NetworkPlayerActorAssignmentDelegate(IEventDataPtr pEventData)
{
	if (!m_bProxy)
		return;

	// we're a remote client getting an actor assignment.
	// the server assigned us a playerId when we first attached (the server's socketId, actually)
	//std::shared_ptr<EvtData_Network_Player_Actor_Assignment> pCastEventData = static_pointer_cast<EvtData_Network_Player_Actor_Assignment>(pEventData);

	/*
	if (pCastEventData->GetActorId() == INVALID_ACTOR_ID)
	{
		m_remotePlayerId = pCastEventData->GetSocketId();
		return;
	}

	for (auto it = m_gameViews.begin(); it != m_gameViews.end(); ++it)
	{
		shared_ptr<IGameView> pView = *it;
		if (pView->VGetType() == GameView_Human)
		{
			shared_ptr<TeapotWarsHumanView> pHumanView = static_pointer_cast<TeapotWarsHumanView, IGameView>(pView);
			if (m_remotePlayerId == pCastEventData->GetSocketId())
			{
				pHumanView->VSetControlledActor(pCastEventData->GetActorId());
			}
			return;
		}
	}

	GCC_ERROR("Could not find HumanView to attach actor to!");
	*/
}

void GameLogic::StartThrustDelegate(IEventDataPtr pEventData)
{
	/*
	std::shared_ptr<EvtData_StartThrust> pCastEventData = static_pointer_cast<EvtData_StartThrust>(pEventData);
	StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEventData->GetActorId()));
	if (pActor)
	{
		shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
		if (pPhysicalComponent)
		{
			pPhysicalComponent->ApplyAcceleration(pCastEventData->GetAcceleration());
		}
	}
	*/
}

void GameLogic::EndThrustDelegate(IEventDataPtr pEventData)
{
	/*
	std::shared_ptr<EvtData_StartThrust> pCastEventData = static_pointer_cast<EvtData_StartThrust>(pEventData);
	StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEventData->GetActorId()));
	if (pActor)
	{
		shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
		if (pPhysicalComponent)
		{
			pPhysicalComponent->RemoveAcceleration();
		}
	}
	*/
}

void GameLogic::StartSteerDelegate(IEventDataPtr pEventData)
{
	/*
	std::shared_ptr<EvtData_StartThrust> pCastEventData = static_pointer_cast<EvtData_StartThrust>(pEventData);
	StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEventData->GetActorId()));
	if (pActor)
	{
		shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
		if (pPhysicalComponent)
		{
			pPhysicalComponent->ApplyAngularAcceleration(pCastEventData->GetAcceleration());
		}
	}
	*/
}

void GameLogic::EndSteerDelegate(IEventDataPtr pEventData)
{
	/*
	shared_ptr<EvtData_StartThrust> pCastEventData = static_pointer_cast<EvtData_StartThrust>(pEventData);
	StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEventData->GetActorId()));
	if (pActor)
	{
		shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
		if (pPhysicalComponent)
		{
			pPhysicalComponent->RemoveAngularAcceleration();
		}
	}
	*/
}

void GameLogic::TestScriptDelegate(IEventDataPtr pEventData)
{
	//shared_ptr<EvtData_ScriptEventTest_FromLua> pCastEventData = static_pointer_cast<EvtData_ScriptEventTest_FromLua>(pEventData);
	//GCC_LOG("Lua", "Event received in C++ from Lua: " + ToStr(pCastEventData->GetNum()));
}

void GameLogic::RegisterAllDelegates(void)
{
	// FUTURE WORK: Lots of these functions are ok to go into the base game logic!
	/*
	IEventManager* pGlobalEventManager = IEventManager::Get();
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::RemoteClientDelegate), EvtData_Remote_Client::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::RequestStartGameDelegate), EvtData_Request_Start_Game::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::NetworkPlayerActorAssignmentDelegate), EvtData_Network_Player_Actor_Assignment::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::EnvironmentLoadedDelegate), EvtData_Environment_Loaded::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::EnvironmentLoadedDelegate), EvtData_Remote_Environment_Loaded::sk_EventType);

	// FUTURE WORK: Only these belong in TeapotWars.
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::StartThrustDelegate), EvtData_StartThrust::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::EndThrustDelegate), EvtData_EndThrust::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::StartSteerDelegate), EvtData_StartSteer::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::EndSteerDelegate), EvtData_EndSteer::sk_EventType);

	pGlobalEventManager->VAddListener(MakeDelegate(this, &TeapotWarsLogic::TestScriptDelegate), EvtData_ScriptEventTest_FromLua::sk_EventType);
	*/
}

void GameLogic::RemoveAllDelegates(void)
{
	// FUTURE WORK: See the note in RegisterDelegates above....
	//IEventManager* pGlobalEventManager = IEventManager::Get();
	/*
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::RemoteClientDelegate), EvtData_Remote_Client::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::RequestStartGameDelegate), EvtData_Request_Start_Game::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::NetworkPlayerActorAssignmentDelegate), EvtData_Network_Player_Actor_Assignment::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::EnvironmentLoadedDelegate), EvtData_Environment_Loaded::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::EnvironmentLoadedDelegate), EvtData_Remote_Environment_Loaded::sk_EventType);
	if (m_bProxy)
	{
		pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::RequestNewActorDelegate), EvtData_Request_New_Actor::sk_EventType);
	}

	// FUTURE WORK: These belong in teapot wars!
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::StartThrustDelegate), EvtData_StartThrust::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::EndThrustDelegate), EvtData_EndThrust::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::StartSteerDelegate), EvtData_StartSteer::sk_EventType);
	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::EndSteerDelegate), EvtData_EndSteer::sk_EventType);

	pGlobalEventManager->VRemoveListener(MakeDelegate(this, &TeapotWarsLogic::TestScriptDelegate), EvtData_ScriptEventTest_FromLua::sk_EventType);
	*/
}

void GameLogic::CreateNetworkEventForwarder(const int socketId)
{
	/*
	NetworkEventForwarder* pNetworkEventForwarder = GCC_NEW NetworkEventForwarder(socketId);

	IEventManager* pGlobalEventManager = IEventManager::Get();

	// then add those events that need to be sent along to amy attached clients
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_PhysCollision::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Destroy_Actor::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Fire_Weapon::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Environment_Loaded::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_New_Actor::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Move_Actor::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Request_New_Actor::sk_EventType);
	pGlobalEventManager->VAddListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Network_Player_Actor_Assignment::sk_EventType);

	m_networkEventForwarders.push_back(pNetworkEventForwarder);
	*/
}

void GameLogic::DestroyAllNetworkEventForwarders(void)
{
	/*
	for (auto it = m_networkEventForwarders.begin(); it != m_networkEventForwarders.end(); ++it)
	{
		NetworkEventForwarder* pNetworkEventForwarder = (*it);

		IEventManager* pGlobalEventManager = IEventManager::Get();
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_PhysCollision::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Destroy_Actor::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Fire_Weapon::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Environment_Loaded::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_New_Actor::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Move_Actor::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Request_New_Actor::sk_EventType);
		pGlobalEventManager->VRemoveListener(MakeDelegate(pNetworkEventForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Network_Player_Actor_Assignment::sk_EventType);

		delete pNetworkEventForwarder;
	}

	m_networkEventForwarders.clear();
	*/
}

bool GameLogic::VLoadGameDelegate(tinyxml2::XMLElement* pLevelData)
{
	//RegisterTeapotScriptEvents();
	return true;
}



