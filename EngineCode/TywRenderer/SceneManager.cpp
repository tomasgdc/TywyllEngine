//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>

//Engine Includes
#include <TywEngine\EventManager\EventManagerImpl.h>


//Renderer Includes
#include "OpenGL\Texture2D.h"
#include "IRenderer.h"
#include "SceneManager.h"

////////////////////////////////////////////////////
// Scene Implementation
////////////////////////////////////////////////////


//
// Scene::Scene						- Chapter 16, page 539
//
//    Note: The shared_ptr<IRenderer> was added to allow for both D3D9 and D3D11 renderer implementations.
//          The book only describes D3D11, so to find all the differences, just search for m_Renderer!
//
SceneManager::SceneManager(std::shared_ptr<IRenderer> renderer)
{
	m_Root.reset(TYW_NEW RootNode());
	m_Renderer = renderer;
	

	m_LightManager = TYW_NEW LightManager;

	//D3DXCreateMatrixStack(0, &m_MatrixStack);

	// [mrmike] - event delegates were added post-press
//	IEventManager* pEventMgr = IEventManager::Get();
//	pEventMgr->VAddListener(MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
//	pEventMgr->VAddListener(MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
//	pEventMgr->VAddListener(MakeDelegate(this, &Scene::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);
//	pEventMgr->VAddListener(MakeDelegate(this, &Scene::ModifiedRenderComponentDelegate), EvtData_Modified_Render_Component::sk_EventType);
}

//
// Scene::~Scene					- Chapter 16, page 539
//
SceneManager::~SceneManager()
{
	// [mrmike] - event delegates were added post-press!
	//EventManager* pEventMgr = EngineSub
//	pEventMgr->VRemoveListener(MakeDelegate(this, &Scene::NewRenderComponentDelegate), EvtData_New_Render_Component::sk_EventType);
//	pEventMgr->VRemoveListener(MakeDelegate(this, &Scene::DestroyActorDelegate), EvtData_Destroy_Actor::sk_EventType);
//	pEventMgr->VRemoveListener(MakeDelegate(this, &Scene::MoveActorDelegate), EvtData_Move_Actor::sk_EventType);

//	pEventMgr->VRemoveListener(MakeDelegate(this, &Scene::ModifiedRenderComponentDelegate), EvtData_Modified_Render_Component::sk_EventType);

//	SAFE_RELEASE(m_MatrixStack);
	
	SAFE_DELETE(m_LightManager);
}

//
// Scene::OnRender					- Chapter 16, page 539
//
HRESULT SceneManager::OnRender()
{
	// The render passes usually go like this 
	// 1. Static objects & terrain
	// 2. Actors (dynamic objects that can move)
	// 3. The Sky
	// 4. Anything with Alpha

	if (m_Root && m_Camera)
	{
		// The scene root could be anything, but it
		// is usually a SceneNode with the identity
		// matrix

		m_Camera->SetViewTransform(this);

		//	m_LightManager->CalcLighting(this);
		if (m_Root->VPreRender(this) == S_OK)
		{
			m_Root->VRender(this);
			m_Root->VRenderChildren(this);
			m_Root->VPostRender(this);
		}
		RenderAlphaPass();
	}

	return S_OK;
}

//
// Scene::OnLostDevice						- not in the book
//
//    All Scene nodes implement VOnLostDevice, which is called in the D3D9 renderer.
//
HRESULT SceneManager::OnLostDevice()
{
	if (m_Root)
	{
		return m_Root->VOnLostDevice(this);
	}
	return S_OK;
}

//
// Scene::OnRestore					- Chapter 16, page 540
//
HRESULT SceneManager::OnRestore()
{
	if (!m_Root)
		return S_OK;

	return m_Root->VOnRestore(this);
}





bool SceneManager::AddChild(ActorId id, std::shared_ptr<ISceneNode> kid)
{
	if (id != INVALID_ACTOR_ID)
	{
		// This allows us to search for this later based on actor id
		m_ActorMap[id] = kid;
	}

	std::shared_ptr<LightNode> pLight = std::dynamic_pointer_cast<LightNode>(kid);
	if (pLight != nullptr && m_LightManager->m_Lights.size() + 1 < MAXIMUM_LIGHTS_SUPPORTED)
	{
		m_LightManager->m_Lights.push_back(pLight);
	}
	return m_Root->VAddChild(kid);
}

bool SceneManager::RemoveChild(ActorId id)
{
	if (id == INVALID_ACTOR_ID)
		return false;
	std::shared_ptr<ISceneNode> kid = FindActor(id);
	std::shared_ptr<LightNode> pLight = std::dynamic_pointer_cast<LightNode>(kid);
	if (pLight != NULL)
	{
		//m_LightManager->m_Lights.remove(pLight);
	}
	m_ActorMap.erase(id);
	return m_Root->VRemoveChild(id);
}



void SceneManager::NewRenderComponentDelegate(IEventDataPtr pEventData)
{
//	std::shared_ptr<EvtData_New_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_New_Render_Component>(pEventData);

	//ActorId actorId = pCastEventData->GetActorId();
	//std::shared_ptr<SceneNode> pSceneNode(pCastEventData->GetSceneNode());

	// FUTURE WORK: Add better error handling here.		
	/*
	if (FAILED(pSceneNode->VOnRestore(this)))
	{
		std::string error = "Failed to restore scene node to the scene for actorid " + ToStr(actorId);
		GCC_ERROR(error);
		return;
	}

	AddChild(actorId, pSceneNode);
	*/
}

void SceneManager::ModifiedRenderComponentDelegate(IEventDataPtr pEventData)
{
	//std::shared_ptr<EvtData_Modified_Render_Component> pCastEventData = std::static_pointer_cast<EvtData_Modified_Render_Component>(pEventData);

	/*
	ActorId actorId = pCastEventData->GetActorId();
	if (actorId == INVALID_ACTOR_ID)
	{
		GCC_ERROR("Scene::ModifiedRenderComponentDelegate - unknown actor id!");
		return;
	}

	if (g_pApp->GetGameLogic()->GetState() == BGS_LoadingGameEnvironment)
		return;
	

	std::shared_ptr<ISceneNode> pSceneNode = FindActor(actorId);
	// FUTURE WORK: Add better error handling here.		
	if (!pSceneNode || FAILED(pSceneNode->VOnRestore(this)))
	{
		GCC_ERROR("Failed to restore scene node to the scene for actorid " + ToStr(actorId));
	}
	*/
}

void SceneManager::DestroyActorDelegate(IEventDataPtr pEventData)
{
	//std::shared_ptr<EvtData_Destroy_Actor> pCastEventData = std::static_pointer_cast<EvtData_Destroy_Actor>(pEventData);
	//RemoveChild(pCastEventData->GetId());
}

void SceneManager::MoveActorDelegate(IEventDataPtr pEventData)
{
//	std::shared_ptr<EvtData_Move_Actor> pCastEventData = static_pointer_cast<EvtData_Move_Actor>(pEventData);

//	ActorId id = pCastEventData->GetId();
//	glx::mat4<float> transform = pCastEventData->GetMatrix();

//	std::shared_ptr<ISceneNode> pNode = FindActor(id);
//	if (pNode)
//	{
//		pNode->VSetTransform(&transform);
//	}
}



//
// Scene::OnUpdate					- Chapter 16, page 540
//
HRESULT SceneManager::OnUpdate(const int deltaMilliseconds)
{
	if (!m_Root)
		return S_OK;

//	static DWORD lastTime = timeGetTime();
//	DWORD elapsedTime = 0;
//	DWORD now = timeGetTime();
	
//	elapsedTime = now - lastTime;
//	lastTime = now;

	return m_Root->VOnUpdate(this, 0);
}

//
// Scene::FindActor					- Chapter 16, page 542
//
std::shared_ptr<ISceneNode> SceneManager::FindActor(ActorId id)
{
	SceneActorMap::iterator i = m_ActorMap.find(id);
	if (i == m_ActorMap.end())
	{
		return std::shared_ptr<ISceneNode>();
	}

	return i->second;
}


//
// Scene::RenderAlphaPass			- Chapter 16, page 543
//
void SceneManager::RenderAlphaPass()
{
	/*
	std::shared_ptr<IRenderState> alphaPass = m_Renderer->VPrepareAlphaPass();

	m_AlphaSceneNodes.sort();
	while (!m_AlphaSceneNodes.empty())
	{
		AlphaSceneNodes::reverse_iterator i = m_AlphaSceneNodes.rbegin();
		PushAndSetMatrix((*i)->m_Concat);
		(*i)->m_pNode->VRender(this);
		delete (*i);
		PopMatrix();
		m_AlphaSceneNodes.pop_back();
	}
	*/
}








