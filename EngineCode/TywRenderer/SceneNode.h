#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "OpenGL\BufferObject.h" //should not be here

#include "Model_local.h"
#include "Material.h"
#include "ISceneNode.h"

// Forward declarations
class SceneNode;
class SceneManager;
class RayCast;
class MovementController;
class IResourceExtraData;
class ActorComponent;
class BaseRenderComponent;
class VertexBuffer;



const ActorId INVALID_ACTOR_ID = 0;


enum RenderPass
{
	RenderPass_0,
	RenderPass_Static = RenderPass_0,
	RenderPass_Actor,
	RenderPass_Sky,
	RenderPass_NotRendered,
	RenderPass_Last
};



// FUTURE WORK - Smart pointers don't work right....going to use a naked pointer for now!
typedef BaseRenderComponent* WeakBaseRenderComponentPtr;

////////////////////////////////////////////////////
//
// AlphaType					- Chapter X, page Y
//
//   This enum defines the different types of alpha blending
//   types that can be set on a scene node.
//
//	
////////////////////////////////////////////////////

enum AlphaType
{
	AlphaOpaque,
	AlphaTexture,
	AlphaMaterial,
	AlphaVertex
};


//////////////////////////////////////////////////////////////////////
//  class SceneNodeProperties	- Chapter 16, page 527
//
//   This class is contained in the SceneNode class, and gains
//   easy access to common scene node properties such as its ActorId
//   or render pass, with a single ISceneNode::VGet() method.
//
//////////////////////////////////////////////////////////////////////

class TYWRENDERER_API SceneNodeProperties
{
	friend class SceneNode;

protected:
	ActorId                 m_ActorId;
	std::string				m_Name;
	glx::mat4<float>		m_ToWorld, m_FromWorld;
	float					m_Radius;
	RenderPass				m_RenderPass;
	Material				m_Material;
	AlphaType				m_AlphaType;

	void SetAlpha(const float alpha)
	{
		m_AlphaType = AlphaMaterial; m_Material.SetAlpha(alpha);
	}

public:
	SceneNodeProperties(void);
	const ActorId &ActorId() const { return m_ActorId; }
	glx::mat4<float> const &ToWorld() const { return m_ToWorld; }
	glx::mat4<float> const &FromWorld() const { return m_FromWorld; }
	void Transform(glx::mat4<float> *toWorld, glx::mat4<float> *fromWorld) const;

	const char * Name() const { return m_Name.c_str(); }

	bool HasAlpha() const { return m_Material.HasAlpha(); }
	float Alpha() const { return m_Material.GetAlpha(); }
	AlphaType AlphaType() const { return m_AlphaType; }

	RenderPass RenderPass() const { return m_RenderPass; }
	float Radius() const { return m_Radius; }

	Material GetMaterial() const { return m_Material; }
};

//////////////////////////////////////////////////////////////
//
// SceneNodeList						- Chapter 16, page 529
//
//   Every scene node has a list of its children - this 
//   is implemented as a vector since it is expected that
//   we won't add/delete nodes very often, and we'll want 
//   fast random access to each child.
//
//////////////////////////////////////////////////////////////

typedef std::vector<std::shared_ptr<ISceneNode> > SceneNodeList;


//////////////////////////////////////////////////////////////
//
// SceneNode							- Chapter 16, page 529
//
//   Implements ISceneNode. Forms the base class for any node
//   that can exist in the 3D scene graph managed by class Scene.
//
//////////////////////////////////////////////////////////////

class TYWRENDERER_API SceneNode : public ISceneNode
{
	friend class Scene;

protected:
	SceneNodeList				 m_Children;
	SceneNode					*m_pParent;
	SceneNodeProperties			 m_Props;
	WeakBaseRenderComponentPtr	 m_RenderComponent;

public:
	SceneNode(ActorId actorId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass, const glx::mat4<float> *to, const glx::mat4<float> *from = nullptr);

	virtual ~SceneNode();

	virtual const SceneNodeProperties* const VGet() const { return &m_Props; }

	virtual void VSetTransform(const glx::mat4<float> *toWorld, const glx::mat4<float> *fromWorld = NULL);

	virtual HRESULT VOnRestore(SceneManager *pScene);
	virtual HRESULT VOnUpdate(SceneManager *, DWORD const elapsedMs);

	virtual HRESULT VPreRender(SceneManager *pScene);
	virtual bool VIsVisible(SceneManager *pScene) const;
	virtual HRESULT VRender(SceneManager *pScene) { return S_OK; }
	virtual HRESULT VRenderChildren(SceneManager *pScene);
	virtual HRESULT VPostRender(SceneManager *pScene);

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual bool VRemoveChild(ActorId id);
	virtual HRESULT VOnLostDevice(SceneManager *pScene);
	virtual HRESULT VPick(SceneManager *pScene, RayCast *pRayCast);

	void SetAlpha(float alpha);
	float GetAlpha() const { return m_Props.Alpha(); }

	glx::vec3<float> GetPosition() const { return m_Props.m_ToWorld.GetPosition(); }
	void SetPosition(const glx::vec3<float> &pos) { m_Props.m_ToWorld.SetPosition(pos); }

	const glx::vec3<float> GetWorldPosition() const;					// [mrmike] added post-press to respect ancestor's position 

	glx::vec3<float> GetDirection() const { return m_Props.m_ToWorld.GetDirection(); }

	void SetRadius(const float radius) { m_Props.m_Radius = radius; }
	void SetMaterial(const Material &mat) { m_Props.m_Material = mat; }
};

//
// class D3DSceneNode9						- not described in the book
// class D3DSceneNode11						- not described in the book
//
// The book only describes a D3D11 render implementations. The engine code implements D3D9 as well as 
//    D3D11, by creating different renderers and scene nodes based on the settings of PlayerOptions.xml.  
//
class D3DSceneNode9 : public SceneNode
{
public:
	D3DSceneNode9(const ActorId actorId,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass,
		const glx::mat4<float> *t)
		: SceneNode(actorId, renderComponent, renderPass, t) { }

	virtual HRESULT VRender(SceneManager *pScene);
};

class D3DSceneNode11 : public SceneNode
{
public:
	virtual HRESULT VRender(SceneManager *pScene) { return S_OK; }
};


////////////////////////////////////////////////////
//
// AlphaSceneNode Description						- Chapter 16, page 535
// AlphaSceneNodes Description						- Chapter 16, page 535
//
// A list of scene nodes that need to be drawn in the alpha pass;
// the list is defined as an STL list
////////////////////////////////////////////////////

struct AlphaSceneNode
{
	std::shared_ptr<ISceneNode> m_pNode;
	glx::mat4<float> m_Concat;
	float m_ScreenZ;

	// For the STL sort...
	bool const operator <(AlphaSceneNode const &other) { return m_ScreenZ < other.m_ScreenZ; }
};

typedef std::list<AlphaSceneNode *> AlphaSceneNodes;


////////////////////////////////////////////////////
//
// SceneActorMap Description
//
//   An STL map that allows fast lookup of a scene node given an ActorId.
//
////////////////////////////////////////////////////

typedef std::map<ActorId, std::shared_ptr<ISceneNode> > SceneActorMap;


////////////////////////////////////////////////////
//
// Scene Description
//
// A heirarchical container of scene nodes, which
// are classes that implemente the ISceneNode interface
//
////////////////////////////////////////////////////

class CameraNode;
class SkyNode;


////////////////////////////////////////////////////
//
// class RootNode					- Chapter 16, page 545
//
//    This is the root node of the scene graph.
//
////////////////////////////////////////////////////

class TYWRENDERER_API RootNode : public SceneNode
{
public:
	RootNode();
	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual HRESULT VRenderChildren(SceneManager *pScene);
	virtual bool VRemoveChild(ActorId id);
	virtual bool VIsVisible(SceneManager *pScene) const { return true; }
};


////////////////////////////////////////////////////
//
// class CameraNode					- Chapter 16, page 548
//
//    A camera node controls the D3D view transform and holds the view
//    frustum definition
//
////////////////////////////////////////////////////

class TYWRENDERER_API CameraNode : public SceneNode
{
public:
	CameraNode(glx::mat4<float> const *t, Frustum const &frustum)
		: SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_0, t),
		m_Frustum(frustum),
		m_bActive(true),
		m_DebugCamera(false),
		m_pTarget(std::shared_ptr<SceneNode>()),
		m_CamOffsetVector(0.0f, 1.0f, -10.0f, 0.0f)
	{
	}

	virtual HRESULT VRender(SceneManager *pScene);
	virtual HRESULT VOnRestore(SceneManager *pScene);
	virtual bool VIsVisible(SceneManager *pScene) const { return m_bActive; }

	const Frustum &GetFrustum() { return m_Frustum; }
	void SetTarget(std::shared_ptr<SceneNode> pTarget)
	{
		m_pTarget = pTarget;
	}
	void ClearTarget() { m_pTarget = std::shared_ptr<SceneNode>(); }
	std::shared_ptr<SceneNode> GetTarget() { return m_pTarget; }

	glx::mat4<float> GetWorldViewProjection(SceneManager *pScene);
	HRESULT SetViewTransform(SceneManager *pScene);

	glx::mat4<float> GetProjection() { return m_Projection; }
	glx::mat4<float> GetView() { return m_View; }

	void SetCameraOffset(const glx::vec4<float> & cameraOffset)
	{
		m_CamOffsetVector = cameraOffset;
	}

protected:

	Frustum			m_Frustum;
	glx::mat4<float>			m_Projection;
	glx::mat4<float>			m_View;
	bool			m_bActive;
	bool			m_DebugCamera;
	std::shared_ptr<SceneNode> m_pTarget;
	glx::vec4<float>			m_CamOffsetVector;	//Direction of camera relative to target.
};




class D3DGrid11 : public SceneNode
{
protected:
	DWORD					m_numVerts;
	DWORD					m_numPolys;

	//    int                     m_squares;

	//ID3D11Buffer*               m_pIndexBuffer;
	//ID3D11Buffer*               m_pVertexBuffer;

	//GameCode4_Hlsl_VertexShader		m_VertexShader;
	//GameCode4_Hlsl_PixelShader		m_PixelShader;

public:
	bool					m_bTextureHasAlpha;

	D3DGrid11(ActorId actorId, WeakBaseRenderComponentPtr renderComponent, /* const std::string& name, const char* textureResource, int squares, const Color &diffuseColor, */ const glx::mat4<float>* pMatrix);
	virtual ~D3DGrid11();
	virtual HRESULT VOnRestore(SceneManager *pScene);
	virtual HRESULT VRender(SceneManager *pScene);
	virtual HRESULT VOnUpdate(SceneManager *pScene, DWORD const elapsedMs) { return S_OK; }
	virtual HRESULT VPick(SceneManager *pScene, RayCast *pRayCast) { return E_FAIL; }

	bool VHasAlpha() const { return m_bTextureHasAlpha; }
};



////////////////////////////////////////////////////
//
// ArrowNode Description
//
//   Graphical object that looks like an arrow - they
//     aren't discussed in the book per se but you see them
//     in a lot of the figures!
//
////////////////////////////////////////////////////

class ArrowNode : public SceneNode
{
protected:
	//ID3DXMesh *m_shaft;
	//ID3DXMesh *m_cone;
	glx::mat4<float> m_coneTrans;
	glx::mat4<float> m_shaftTrans;

public:
	ArrowNode(std::string name, WeakBaseRenderComponentPtr renderComponent, const float length, const glx::mat4<float> *t, const glx::vec4<float> &color);

	//virtual ~ArrowNode() { SAFE_RELEASE(m_shaft); SAFE_RELEASE(m_cone); }
	virtual ~ArrowNode(){}
	virtual HRESULT VRender(SceneManager *pScene);
	virtual HRESULT VPick(SceneManager *pScene, RayCast *pRayCast);
};


////////////////////////////////////////////////////
//
// TestObject Description
//
//	Implements test object. It creates cube, updates it and renders it.
//
////////////////////////////////////////////////////
class TYWRENDERER_API TestCube final : public SceneNode
{
protected:
	VertexBuffer			m_VertexBuffer;
	IndexBuffer				m_IndexBuffer;

	DWORD					m_numVerts;
	DWORD					m_numPolys;

	DWORD					m_color;
	bool					m_squashed;

	glx::mat4<float>	    m_modelMatrix;
	glx::mat4<float>		m_viewMatrix;
	glx::mat4<float>		m_projectionMatrix;
	glx::mat4<float>		m_rotationMatrix;
public:
	TestCube(std::string name, glx::vec3<float> pos);
	~TestCube();
	HRESULT VOnRestore(SceneManager *pScene);
	HRESULT VRender(SceneManager *pScene);
	HRESULT VOnUpdate(SceneManager *, DWORD const elapsedMs);


	static WORD g_TestObjectIndices[][3];
	static glx::vec3<float> g_CubeVerts[];
	static glx::vec3<float> g_SquashedCubeVerts[];
};


////////////////////////////////////////////////////
//
// TestObject Description
//
//	Implements test object. It creates cube, updates it and renders it.
//
////////////////////////////////////////////////////
class TYWRENDERER_API TestTriangle final : public SceneNode
{
protected:
	VertexBuffer			m_VertexBuffer;
	IndexBuffer				m_IndexBuffer;

	DWORD					m_numVerts;
	DWORD					m_numPolys;

	DWORD					m_color;
	bool					m_squashed;

	glx::mat4<float>	    m_modelMatrix;
	glx::mat4<float>		m_viewMatrix;
	glx::mat4<float>		m_projectionMatrix;
	glx::mat4<float>		m_rotationMatrix;
public:
	TestTriangle(std::string name, glx::vec3<float> pos);
	virtual ~TestTriangle();
	HRESULT VOnRestore(SceneManager *pScene);
	HRESULT VRender(SceneManager *pScene);
	HRESULT VOnUpdate(SceneManager *, DWORD const elapsedMs);


	static WORD g_TestObjectIndices[][3];
	static glx::vec3<float> g_CubeVerts[];
	static glx::vec3<float> g_SquashedCubeVerts[];
};

#endif
