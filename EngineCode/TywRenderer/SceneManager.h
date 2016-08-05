#ifndef _SCENE_H_
#define _SCENEN_H_
#include "Model_local.h"
#include "SceneNode.h"





//Forward declaration
class CameraNode;
class SkyNode;
class LightNode;
class LightManager;
class IRenderer;


//SceneManager specific data declaration
typedef std::map<ActorId, std::shared_ptr<ISceneNode> > SceneActorMap;






/*
	SceneManager manages SceneNodes. It creates new nodes, detaches existing ones,
	traverses scenegraph and renders it.
*/
class TYWRENDERER_API SceneManager
{
protected:
	std::shared_ptr<SceneNode>  	m_Root;
	std::shared_ptr<CameraNode> 	m_Camera;
	std::shared_ptr<IRenderer>		m_Renderer;

	AlphaSceneNodes 		m_AlphaSceneNodes;
	SceneActorMap 			m_ActorMap;
	LightManager			*m_LightManager;
	void RenderAlphaPass();

public:
	SceneManager(std::shared_ptr<IRenderer> renderer = nullptr);
	virtual ~SceneManager();

	HRESULT OnRender();
	HRESULT OnRestore();
	HRESULT OnLostDevice();
	HRESULT OnUpdate(const int deltaMilliseconds);
	std::shared_ptr<ISceneNode> FindActor(ActorId id);
	bool AddChild(ActorId id, std::shared_ptr<ISceneNode> kid);
	bool RemoveChild(ActorId id);

	// event delegates
	void NewRenderComponentDelegate(IEventDataPtr pEventData);
	void ModifiedRenderComponentDelegate(IEventDataPtr pEventData);			// added post-press!
	void DestroyActorDelegate(IEventDataPtr pEventData);
	void MoveActorDelegate(IEventDataPtr pEventData);

	void SetCamera(std::shared_ptr<CameraNode> camera) { m_Camera = camera; }
	const std::shared_ptr<CameraNode> GetCamera() const { return m_Camera; }


	void PushAndSetMatrix(const glx::mat4<float> &toWorld)
	{
		// Note this code carefully!!!!! It is COMPLETELY different
		// from some DirectX 9 documentation out there....
		// Scene::PushAndSetMatrix - Chapter 16, page 541

		//m_MatrixStack->Push();
		//m_MatrixStack->MultMatrixLocal(&toWorld);
		glx::mat4<float> mat = GetTopMatrix();
		//m_Renderer->VSetWorldTransform(&mat);
	}

	void PopMatrix()
	{
		// Scene::PopMatrix - Chapter 16, page 541
		//m_MatrixStack->Pop();
		glx::mat4<float> mat = GetTopMatrix();
		//m_Renderer->VSetWorldTransform(&mat);
	}

	const glx::mat4<float> GetTopMatrix()
	{
		// Scene::GetTopMatrix - Chapter 16, page 541
		//return static_cast<const glx::mat4<float>>(*m_MatrixStack->GetTop());

		const glx::mat4<float> t;

		return t;
	}

	LightManager *GetLightManager() { return m_LightManager; }

	void AddAlphaSceneNode(AlphaSceneNode *asn) { m_AlphaSceneNodes.push_back(asn); }

	HRESULT Pick(RayCast *pRayCast) { return m_Root->VPick(this, pRayCast); }

	std::shared_ptr<IRenderer> GetRenderer() { return m_Renderer; }
};
#endif
