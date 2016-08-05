#ifndef _I_SCENE_NODE_H_
#define _I_SCENE_NODE_H_

//forward declaration
class SceneNodeProperties;
class SceneManager;
class RayCast;

typedef int ActorId;

class ISceneNode
{
public:
	virtual const SceneNodeProperties * const VGet() const = 0;

	virtual void VSetTransform(const glx::mat4<float> *toWorld, const glx::mat4<float> *fromWorld = NULL) = 0;

	virtual HRESULT VOnUpdate(SceneManager *pScene, DWORD const elapsedMs) = 0;
	virtual HRESULT VOnRestore(SceneManager *pScene) = 0;

	virtual HRESULT VPreRender(SceneManager *pScene) = 0;
	virtual bool VIsVisible(SceneManager *pScene) const = 0;
	virtual HRESULT VRender(SceneManager *pScene) = 0;
	virtual HRESULT VRenderChildren(SceneManager *pScene) = 0;
	virtual HRESULT VPostRender(SceneManager *pScene) = 0;

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid) = 0;
	virtual bool VRemoveChild(ActorId id) = 0;
	virtual HRESULT VOnLostDevice(SceneManager *pScene) = 0;
	virtual HRESULT VPick(SceneManager *pScene, RayCast *pRayCast) = 0;


	virtual ~ISceneNode() { };
};
#endif
