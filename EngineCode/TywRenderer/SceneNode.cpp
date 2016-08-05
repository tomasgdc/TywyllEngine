//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>

//Game Includes
#include <TywGame\Actors\RenderingComponent.h>

//Engine Includes
#include <TywEngine\EventManager\IEventManager.h>

//Renderer Includes
#include "GLRenderer.h"
#include "SceneManager.h"
#include "RayCast.h"
#include "SceneNode.h"
#include "OpenGL\Texture2D.h"
#include "RenderProgs.h"



////////////////////////////////////////////////////
// SceneNodeProperties Implementation
////////////////////////////////////////////////////
SceneNodeProperties::SceneNodeProperties(void)
{
	m_ActorId = INVALID_ACTOR_ID;
	m_Radius = 0;
	m_RenderPass = RenderPass_0;
	m_AlphaType = AlphaOpaque;
}


//
// SceneNodeProperties::Transform	
void SceneNodeProperties::Transform(glx::mat4<float> *toWorld, glx::mat4<float>*fromWorld) const
{
	if (toWorld)
		*toWorld = m_ToWorld;

	if (fromWorld)
		*fromWorld = m_FromWorld;
}


////////////////////////////////////////////////////
// SceneNode Implementation
////////////////////////////////////////////////////
SceneNode::SceneNode(ActorId actorId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass, const glx::mat4<float> *to, const glx::mat4<float> *from)
{
	m_pParent = NULL;
	m_Props.m_ActorId = actorId;
	m_Props.m_Name = (renderComponent) ? renderComponent->VGetName() : "SceneNode";
	m_Props.m_RenderPass = renderPass;
	m_Props.m_AlphaType = AlphaOpaque;
	m_RenderComponent = renderComponent;
	//VSetTransform(to, from);
	SetRadius(0);

	// [mrmike] - these lines were moved to VOnRestore() post press
	//Color color = (renderComponent) ? renderComponent->GetColor() : g_White;
	//m_Props.m_Material.SetDiffuse(color);
}


SceneNode::~SceneNode()
{
}

//
// SceneNode::VOnRestore			
HRESULT SceneNode::VOnRestore(SceneManager *pScene)
{
	//glx::vec4<float> color = (m_RenderComponent) ? m_RenderComponent->GetColor() : g_White;
	//m_Props.m_Material.SetDiffuse(color);

	// This is meant to be called from any class
	// that inherits from SceneNode and overloads
	//VOnRestore(pScene);

	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();
	while (i != end)
	{
		(*i)->VOnRestore(pScene);
		++i;
	}
	return S_OK;
}


//
// SceneNode::VOnLostDevice	
HRESULT SceneNode::VOnLostDevice(SceneManager *pScene)
{
	// This is meant to be called from any class
	// that inherits from SceneNode and overloads
	// VOnRestore()

	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();
	while (i != end)
	{
		(*i)->VOnLostDevice(pScene);
		++i;
	}
	return S_OK;
}

//
// SceneNode::VSetTransform	
void SceneNode::VSetTransform(const glx::mat4<float> *toWorld, const glx::mat4<float> *fromWorld)
{
	m_Props.m_ToWorld = *toWorld;
	if (!fromWorld)
	{
		float determinant = GLXMatrixDeterminant(&m_Props.m_ToWorld);
		GLXMatrixInverse(&m_Props.m_FromWorld, determinant, &m_Props.m_ToWorld);
	}
	else
	{
		m_Props.m_FromWorld = *fromWorld;
	}
}


//
// SceneNode::VPreRender		
HRESULT SceneNode::VPreRender(SceneManager *pScene)
{
	// This was added post press! Is is always ok to read directly from the game logic.
	StrongActorPtr pActor; // = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(m_Props.m_ActorId));
	if (pActor)
	{
		//std::shared_ptr<TransformComponent> pTc; // MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
		//if (pTc)
		//{
	//		m_Props.m_ToWorld = pTc->GetTransform();
//		}
	}

	pScene->PushAndSetMatrix(m_Props.m_ToWorld);
	return S_OK;
}

//
// SceneNode::VPostRender
HRESULT SceneNode::VPostRender(SceneManager *pScene)
{
	pScene->PopMatrix();
	return S_OK;
}



//
// SceneNode::VIsVisible		
bool SceneNode::VIsVisible(SceneManager *pScene) const
{
	// transform the location of this node into the camera space 
	// of the camera attached to the scene

	glx::mat4<float> toWorld, fromWorld;
	pScene->GetCamera()->VGet()->Transform(&toWorld, &fromWorld);

	glx::vec3<float> pos = GetWorldPosition();

	
	glx::vec3<float> fromWorldPos = GLXVec3Transform(&pos, &fromWorld);

	Frustum const &frustum = pScene->GetCamera()->GetFrustum();

	bool isVisible = frustum.Inside(fromWorldPos, VGet()->Radius());
	return isVisible;
}

//
// SceneNode::GetWorldPosition			- not described in the book
//
//   This was added post press to respect any SceneNode ancestors - you have to add all 
//   their positions together to get the world position of any SceneNode.
//
const glx::vec3<float> SceneNode::GetWorldPosition() const
{
	glx::vec3<float> pos = GetPosition();
	if (m_pParent)
	{
		pos += m_pParent->GetWorldPosition();
	}
	return pos;
}


//
// SceneNode::VOnUpdate			
HRESULT SceneNode::VOnUpdate(SceneManager *pScene, DWORD const elapsedMs)
{
	// This is meant to be called from any class
	// that inherits from SceneNode and overloads
	// VOnUpdate()

	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();

	while (i != end)
	{
		(*i)->VOnUpdate(pScene, elapsedMs);
		++i;
	}
	return S_OK;
}


//
// SceneNode::VRender		
HRESULT D3DSceneNode9::VRender(SceneManager *pScene)
{
//	m_Props.GetMaterial().D3DUse9();

	switch (m_Props.AlphaType())
	{
	case AlphaTexture:
		// Nothing to do here....
		break;

	case AlphaMaterial:
	//	DXUTGetD3D9Device()->SetRenderState(D3DRS_COLORVERTEX, true);
	//	DXUTGetD3D9Device()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		break;

	case AlphaVertex:
		assert(0 && "Not implemented!");
		break;
	}

	return S_OK;
}

//
// SceneNode::VRenderChildren			
HRESULT SceneNode::VRenderChildren(SceneManager *pScene)
{
	// Iterate through the children....
	SceneNodeList::iterator i = m_Children.begin();
	SceneNodeList::iterator end = m_Children.end();

	while (i != end)
	{
		if ((*i)->VPreRender(pScene) == S_OK)
		{
			// You could short-circuit rendering
			// if an object returns E_FAIL from
			//VPreRender(pScene);

			// Don't render this node if you can't see it
			//if ((*i)->VIsVisible(pScene))
			//{
				float alpha = (*i)->VGet()->m_Material.GetAlpha();
				(*i)->VRender(pScene);

				if (alpha == 1.0f)
				{
					
				}
				/*
				else if (alpha != 1.0f)
				{
					// The object isn't totally transparent...
					AlphaSceneNode *asn = TYW_NEW AlphaSceneNode;
					assert(asn);
					asn->m_pNode = *i;
					asn->m_Concat = pScene->GetTopMatrix();

					glx::vec4<float> worldPos(asn->m_Concat.GetPosition());

					glx::mat4<float> fromWorld = pScene->GetCamera()->VGet()->FromWorld();

					glx::vec4<float> screenPos;// = fromWorld.Xform(worldPos);

					asn->m_ScreenZ = screenPos.z;

					pScene->AddAlphaSceneNode(asn);
				}
				*/

				// [mrmike] see comment just below...
				(*i)->VRenderChildren(pScene);
			}

			// [mrmike] post-press fix - if the parent is not visible, the childrend
			//           shouldn't be visible either.
			//(*i)->VRenderChildren(pScene);
		//}
		(*i)->VPostRender(pScene);
		++i;
	}

	return S_OK;
}


//
// SceneNode::VAddChild
bool SceneNode::VAddChild(std::shared_ptr<ISceneNode> ikid)
{
	m_Children.push_back(ikid);

	std::shared_ptr<SceneNode> kid = std::static_pointer_cast<SceneNode>(ikid);

	kid->m_pParent = this;					// [mrmike] Post-press fix - the parent was never set!

											// The radius of the sphere should be fixed right here
	glx::vec3<float> kidPos = kid->VGet()->ToWorld().GetPosition();

	// [mrmike] - Post-press fix. This was not correct! subtracting the parents's position from the kidPos
	//            created a HUGE radius, depending on the location of the parent, which could be anywhere
	//            in the game world.

	//Vec3 dir = kidPos - m_Props.ToWorld().GetPosition();
	//float newRadius = dir.Length() + kid->VGet()->Radius();

	float newRadius = 0;// = kidPos.Length() + kid->VGet()->Radius();

	if (newRadius > m_Props.m_Radius)
		m_Props.m_Radius = newRadius;

	return true;
}

//
// SceneNode::VRemoveChild					- not in the book
//
//   If an actor is destroyed it should be removed from the scene graph.
//   Generally the HumanView will recieve a message saying the actor has been
//   destroyed, and it will then call Scene::RemoveChild which will traverse 
//   the scene graph to find the child that needs removing.
//
bool SceneNode::VRemoveChild(ActorId id)
{
	for (SceneNodeList::iterator i = m_Children.begin(); i != m_Children.end(); ++i)
	{
		const SceneNodeProperties* pProps = (*i)->VGet();
		if (pProps->ActorId() != INVALID_ACTOR_ID && id == pProps->ActorId())
		{
			i = m_Children.erase(i);	//this can be expensive for vectors
			return true;
		}
	}
	return false;
}



HRESULT SceneNode::VPick(SceneManager *pScene, RayCast *raycast)
{
	for (SceneNodeList::const_iterator i = m_Children.begin(); i != m_Children.end(); ++i)
	{
		HRESULT hr = (*i)->VPick(pScene, raycast);

		if (hr == E_FAIL)
			return E_FAIL;
	}

	return S_OK;
}

// This was changed post press - it was convenient to be able to set alpha on a parent node and
// have it propagate to all its children, since materials are set in the SceneNodes's properties, and
// not as a SceneNode that changes renderstate by itself.
void SceneNode::SetAlpha(float alpha)
{
	m_Props.SetAlpha(alpha);
	for (SceneNodeList::const_iterator i = m_Children.begin(); i != m_Children.end(); ++i)
	{
		std::shared_ptr<SceneNode> sceneNode = std::static_pointer_cast<SceneNode>(*i);
		sceneNode->SetAlpha(alpha);
	}
}



////////////////////////////////////////////////////
// RootNode Implementation
////////////////////////////////////////////////////

//
// RootNode::RootNode					- Chapter 16, page 545
//
RootNode::RootNode()
	: SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_0, nullptr)//&Mat4x4::g_Identity)
{
	m_Children.reserve(RenderPass_Last);

	
	std::shared_ptr<SceneNode> staticGroup(TYW_NEW SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_Static, nullptr));
	m_Children.push_back(staticGroup);	// RenderPass_Static = 0

	std::shared_ptr<SceneNode> actorGroup(TYW_NEW SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_Actor, nullptr));
	m_Children.push_back(actorGroup);	// RenderPass_Actor = 1

	std::shared_ptr<SceneNode> skyGroup(TYW_NEW SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_Sky, nullptr));
	m_Children.push_back(skyGroup);	// RenderPass_Sky = 2

	std::shared_ptr<SceneNode> invisibleGroup(TYW_NEW SceneNode(INVALID_ACTOR_ID, WeakBaseRenderComponentPtr(), RenderPass_NotRendered, nullptr));
	m_Children.push_back(invisibleGroup);	// RenderPass_NotRendered = 3
}



bool RootNode::VAddChild(std::shared_ptr<ISceneNode> kid)
{
	// The Root node has children that divide the scene graph into render passes.
	// Scene nodes will get added to these children based on the value of the
	// render pass member variable.

	RenderPass pass = kid->VGet()->RenderPass();
	if ((unsigned)pass >= m_Children.size() || !m_Children[pass])
	{
		//assert(0 && "There is no such render pass");
		return false;
	}

	return m_Children[pass]->VAddChild(kid);
}


bool RootNode::VRemoveChild(ActorId id)
{
	bool anythingRemoved = false;
	for (int i = RenderPass_0; i<RenderPass_Last; ++i)
	{
		if (m_Children[i]->VRemoveChild(id))
		{
			anythingRemoved = true;
		}
	}
	return anythingRemoved;
}


HRESULT RootNode::VRenderChildren(SceneManager *pScene)
{
	// This code creates fine control of the render passes.
	for (int pass = RenderPass_0; pass < RenderPass_Last; ++pass)
	{
		switch (pass)
		{
		case RenderPass_Static:
		case RenderPass_Actor:
			m_Children[pass]->VRenderChildren(pScene);
			break;

		case RenderPass_Sky:
		{
			//std::shared_ptr<IRenderState> skyPass = pScene->GetRenderer()->VPrepareSkyBoxPass();
			//m_Children[pass]->VRenderChildren(pScene);
			break;
		}
		}
	}

	return S_OK;
}


////////////////////////////////////////////////////
// CameraNode Implementation
////////////////////////////////////////////////////
HRESULT CameraNode::VRender(SceneManager *pScene)
{
	if (m_DebugCamera)
	{
		pScene->PopMatrix();

		m_Frustum.Render();

		pScene->PushAndSetMatrix(m_Props.ToWorld());
	}

	return S_OK;
}

//
// CameraNode::VOnRestore				- Chapter 16, page 550
//
HRESULT CameraNode::VOnRestore(SceneManager *pScene)
{
	//m_Frustum.SetAspect(DXUTGetWindowWidth() / (FLOAT)DXUTGetWindowHeight());
	//D3DXMatrixPerspectiveFovLH(&m_Projection, m_Frustum.m_Fov, m_Frustum.m_Aspect, m_Frustum.m_Near, m_Frustum.m_Far);
	
	g_pRendGL->VSetProjectionTransform(&m_Projection);
	return S_OK;
}


HRESULT CameraNode::SetViewTransform(SceneManager *pScene)
{
	//If there is a target, make sure the camera is
	//rigidly attached right behind the target
	if (m_pTarget)
	{
		glx::mat4<float> mat = m_pTarget->VGet()->ToWorld();
		glx::vec4<float> at = m_CamOffsetVector;
		glx::vec4<float> atWorld;// = mat.Xform(at);
		glx::vec3<float> pos;// = mat.GetPosition() + Vec3(atWorld);
		mat.SetPosition(pos);
		VSetTransform(&mat);
	}
	m_View = VGet()->FromWorld();
	GLXLookAt(&m_View, glx::vec3<float>(0, 0, 8), glx::vec3<float>(0, 0, 0), glx::vec3<float>(0, 1, 0));

	return S_OK;
}


// Returns the concatenation of the world and view projection, which is generally sent into vertex shaders
glx::mat4<float> CameraNode::GetWorldViewProjection(SceneManager *pScene)
{
	glx::mat4<float> world = pScene->GetTopMatrix();
	glx::mat4<float> view = VGet()->FromWorld();
	glx::mat4<float> worldView = world * view;
	return worldView * m_Projection;
}





D3DGrid11::D3DGrid11(ActorId actorId, WeakBaseRenderComponentPtr renderComponent, const glx::mat4<float>* pMatrix)
	: SceneNode(actorId, renderComponent, RenderPass_0, pMatrix)
{
	m_bTextureHasAlpha = false;
	m_numVerts = m_numPolys = 0;
	//m_pVertexBuffer = NULL;
	//m_pIndexBuffer = NULL;
}

D3DGrid11::~D3DGrid11()
{
	//SAFE_DELETE(m_pVertexBuffer);
	//SAFE_DELETE(m_pIndexBuffer);
}



HRESULT D3DGrid11::VOnRestore(SceneManager *pScene)
{
	HRESULT hr;

	/*
	V_RETURN(SceneNode::VOnRestore(pScene));

	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);

	V_RETURN(m_VertexShader.OnRestore(pScene));
	V_RETURN(m_PixelShader.OnRestore(pScene));

	GridRenderComponent* grc = static_cast<GridRenderComponent*>(m_RenderComponent);

	int squares = grc->GetDivision();

	SetRadius(sqrt(squares * squares / 2.0f));

	// Create the vertex buffer - we'll need enough verts
	// to populate the grid. If we want a 2x2 grid, we'll
	// need 3x3 set of verts.
	m_numVerts = (squares + 1)*(squares + 1);    // Create vertex buffer

												 // Fill the vertex buffer. We are setting the tu and tv texture
												 // coordinates, which range from 0.0 to 1.0
	D3D11Vertex_UnlitTextured *pVerts = GCC_NEW D3D11Vertex_UnlitTextured[m_numVerts];
	GCC_ASSERT(pVerts && "Out of memory in D3DGrid11::VOnRestore()");
	if (!pVerts)
		return E_FAIL;

	for (int j = 0; j<(squares + 1); j++)
	{
		for (int i = 0; i<(squares + 1); i++)
		{
			// Which vertex are we setting?
			int index = i + (j * (squares + 1));
			D3D11Vertex_UnlitTextured *vert = &pVerts[index];

			// Default position of the grid is centered on the origin, flat on
			// the XZ plane.
			float x = (float)i - (squares / 2.0f);
			float y = (float)j - (squares / 2.0f);
			vert->Pos = Vec3(x, 0.f, y);
			vert->Normal = Vec3(0.0f, 1.0f, 0.0f);

			// The texture coordinates are set to x,y to make the
			// texture tile along with units - 1.0, 2.0, 3.0, etc.
			vert->Uv.x = x;
			vert->Uv.y = y;
		}
	}

	// The number of indicies equals the number of polygons times 3
	// since there are 3 indicies per polygon. Each grid square contains
	// two polygons. The indicies are 16 bit, since our grids won't
	// be that big!

	m_numPolys = squares * squares * 2;

	WORD *pIndices = GCC_NEW WORD[m_numPolys * 3];

	GCC_ASSERT(pIndices && "Out of memory in D3DGrid11::VOnRestore()");
	if (!pIndices)
		return E_FAIL;

	// Loop through the grid squares and calc the values
	// of each index. Each grid square has two triangles:
	//
	//		A - B
	//		| / |
	//		C - D

	WORD *current = pIndices;
	for (int j = 0; j<squares; j++)
	{
		for (int i = 0; i<squares; i++)
		{
			// Triangle #1  ACB
			*(current) = WORD(i + (j*(squares + 1)));
			*(current + 1) = WORD(i + ((j + 1)*(squares + 1)));
			*(current + 2) = WORD((i + 1) + (j*(squares + 1)));

			// Triangle #2  BCD
			*(current + 3) = WORD((i + 1) + (j*(squares + 1)));
			*(current + 4) = WORD(i + ((j + 1)*(squares + 1)));
			*(current + 5) = WORD((i + 1) + ((j + 1)*(squares + 1)));
			current += 6;
		}
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(D3D11Vertex_UnlitTextured) * m_numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pVerts;
	hr = DXUTGetD3D11Device()->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (SUCCEEDED(hr))
	{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * m_numPolys * 3;        // 36 vertices needed for 12 triangles in a triangle list
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = pIndices;
		hr = DXUTGetD3D11Device()->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
	}

	SAFE_DELETE_ARRAY(pVerts);
	SAFE_DELETE_ARRAY(pIndices);
	*/


	return hr;
}


HRESULT D3DGrid11::VRender(SceneManager *pScene)
{
	HRESULT hr;

	/*
	GridRenderComponent* grc = static_cast<GridRenderComponent*>(m_RenderComponent);
	m_PixelShader.SetTexture(grc->GetTextureResource());

	V_RETURN(m_VertexShader.SetupRender(pScene, this));
	V_RETURN(m_PixelShader.SetupRender(pScene, this));

	// Set vertex buffer
	UINT stride = sizeof(D3D11Vertex_UnlitTextured);
	UINT offset = 0;
	DXUTGetD3D11DeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set index buffer
	DXUTGetD3D11DeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	DXUTGetD3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DXUTGetD3D11DeviceContext()->DrawIndexed(m_numPolys * 3, 0, 0);
	*/

	return S_OK;
}



////////////////////////////////////////////////////
// ArrowNode Implementation - added post press
////////////////////////////////////////////////////

ArrowNode::ArrowNode(std::string name, WeakBaseRenderComponentPtr renderComponent, const float length, const glx::mat4<float> *t, const glx::vec4<float> &diffuseColor)
	: SceneNode(INVALID_ACTOR_ID, renderComponent, RenderPass_0, t)
{
	//D3DXCreateCylinder(DXUTGetD3D9Device(), 0.1f * length, 0.0f, 0.3f * length, 16, 1, &m_cone, NULL);
	//D3DXCreateCylinder(DXUTGetD3D9Device(), 0.05f * length, 0.05f * length, 0.7f * length, 16, 2, &m_shaft, NULL);

	//m_coneTrans.BuildTranslation(0, 0, (0.7f + 0.15f) * length);
	//m_shaftTrans.BuildTranslation(0, 0, (0.35f * length));

	// The anchor point is at 0,0,0 - so the radius must incorporate the whole length.
	SetRadius(length);
}

HRESULT ArrowNode::VRender(SceneManager *pScene)
{
	if (S_OK != SceneNode::VRender(pScene))
		return E_FAIL;

	pScene->PushAndSetMatrix(m_shaftTrans);

	//m_shaft->DrawSubset(0);
	pScene->PopMatrix();

	pScene->PushAndSetMatrix(m_coneTrans);
	//m_cone->DrawSubset(0);

	pScene->PopMatrix();
	return S_OK;
}


HRESULT ArrowNode::VPick(SceneManager *pScene, RayCast *pRayCast)
{
	if (SceneNode::VPick(pScene, pRayCast) == E_FAIL)
		return E_FAIL;

	pScene->PushAndSetMatrix(m_shaftTrans);
	HRESULT hr;// = pRayCast->Pick(pScene, m_Props.ActorId(), m_shaft);
	pScene->PopMatrix();

	if (hr == E_FAIL)
		return hr;

	pScene->PushAndSetMatrix(m_coneTrans);
	//hr = pRayCast->Pick(pScene, m_Props.ActorId(), m_cone);
	pScene->PopMatrix();

	return hr;
}





////////////////////////////////////////////////////
// TestObject Implementation
//
//
////////////////////////////////////////////////////
TestCube::TestCube(std::string name, glx::vec3<float> pos)
	: SceneNode(0, WeakBaseRenderComponentPtr(), RenderPass_Actor, NULL)
{
	GLXMatrixIdentity(&m_projectionMatrix);
	GLXMatrixIdentity(&m_viewMatrix);
	GLXMatrixIdentity(&m_rotationMatrix);
	GLXMatrixIdentity(&m_modelMatrix);
	GLXMatrixTranslationRM(&m_modelMatrix, pos.x, pos.y, pos.z);

	m_color = 0xffffffff;
	m_numVerts = m_numPolys = 0;
}


TestCube::~TestCube()
{
	//delete buffers
	m_VertexBuffer.FreeBufferObject();
	m_IndexBuffer.FreeBufferObject();
}




HRESULT TestCube::VOnRestore(SceneManager *pScene)
{
	// Call the base class's restore
	SceneNode::VOnRestore(pScene);

	const drawVert g_vertex_buffer_data[] = {
		//First Side
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(-1.0f,-1.0f, 1.0f), glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1)},
		{glx::vec3<float>(-1.0f, 1.0f, 1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(1,0)},

		{glx::vec3<float>(1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0)},
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,1)},
		{glx::vec3<float>(-1.0f, 1.0f,-1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(1,1)},

		//Second side
		{glx::vec3<float>(1.0f,-1.0f, 1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f), glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{glx::vec3<float>(1.0f,-1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		
		{glx::vec3<float>(1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		{glx::vec3<float>(1.0f,-1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) },
		
		//Third Side
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(-1.0f, 1.0f, 1.0f),  glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{glx::vec3<float>(-1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		
		{glx::vec3<float>(1.0f,-1.0f, 1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		{glx::vec3<float>(-1.0f,-1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
		{glx::vec3<float>(-1.0f,-1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) },
		
		//Fourth Side
		{glx::vec3<float>(-1.0f, 1.0f, 1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(-1.0f,-1.0f, 1.0f), glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{glx::vec3<float>(1.0f,-1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		
		{glx::vec3<float>(1.0f, 1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		{glx::vec3<float>(1.0f,-1.0f,-1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
		{glx::vec3<float>(1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) },
		
		//Fifth Side
		{glx::vec3<float>(1.0f,-1.0f,-1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(1.0f, 1.0f, 1.0f),  glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{glx::vec3<float>(1.0f,-1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		
		{glx::vec3<float>(1.0f, 1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		{glx::vec3<float>(1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
		{glx::vec3<float>(-1.0f, 1.0f,-1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) },
		
		//Sixth Side

		{glx::vec3<float>(1.0f, 1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{glx::vec3<float>(-1.0f, 1.0f,-1.0f), glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{glx::vec3<float>(-1.0f, 1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		
		{glx::vec3<float>(1.0f, 1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
		{glx::vec3<float>(-1.0f, 1.0f, 1.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
		{glx::vec3<float>(1.0f,-1.0f, 1.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) },
	};

	//Alocate memory
	m_VertexBuffer.AllocateBufferObject(g_vertex_buffer_data, sizeof(drawVert) * 6 * 3, enumBuffer::STATIC_DRAW);


	//Set positions
	GLXMatrixPerspectiveRM(&m_projectionMatrix, 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	GLXMatrixRotate(&m_rotationMatrix, 260, 1.0f, 0.0f, 0.0f);
	GLXMatrixScaling(&m_modelMatrix, 1.0f, 1.0f, 1.0f);
	GLXLookAt(&m_viewMatrix, glx::vec3<float>(0, 0, 8), glx::vec3<float>(0, 0, 0), glx::vec3<float>(0, 1, 0));
	return S_OK;
}


HRESULT TestCube::VRender(SceneManager *pScene)
{
	if (S_OK != SceneNode::VRender(pScene))
		return E_FAIL;




	m_VertexBuffer.EnableVAO();
	m_VertexBuffer.EnableVBO();
	//m_IndexBuffer.EnableVBO();

	glx::mat4<float> mvp = m_rotationMatrix  * m_modelMatrix * m_viewMatrix * m_projectionMatrix;
	renderProgManager.SetUniformMatrix4fv("geo.glsl", "mvp", 1, false, mvp);

	glDrawArrays(GL_TRIANGLES, 0, 12*3);



	//Resotre state
	m_VertexBuffer.DisableVAO();
	m_VertexBuffer.DisableVBO();

	return S_OK;
}

HRESULT TestCube::VOnUpdate(SceneManager *, DWORD const elapsedMs)
{
	

//	glx::mat4<float> mvp = m_rotationMatrix  * m_modelMatrix * m_viewMatrix * m_projectionMatrix;
//	renderProgManager.SetUniformMatrix4fv("geo.glsl", "mvp", 1, false, mvp);
	return S_OK;
}


TestTriangle::TestTriangle(std::string name, glx::vec3<float> pos)
	: SceneNode(0, WeakBaseRenderComponentPtr(), RenderPass_Actor, NULL)
{
	GLXMatrixIdentity(&m_projectionMatrix);
	GLXMatrixIdentity(&m_viewMatrix);
	GLXMatrixIdentity(&m_rotationMatrix);
	GLXMatrixIdentity(&m_modelMatrix);
	GLXMatrixTranslationRM(&m_modelMatrix, pos.x, pos.y, pos.z);

	m_color = 0xffffffff;
	m_numVerts = m_numPolys = 0;
}


TestTriangle::~TestTriangle()
{
	//delete buffers
	m_VertexBuffer.FreeBufferObject();
	m_IndexBuffer.FreeBufferObject();
}




HRESULT TestTriangle::VOnRestore(SceneManager *pScene)
{
	// Call the base class's restore
	SceneNode::VOnRestore(pScene);

	const drawVert g_vertex_buffer_data[] = {
		//First Side
		{ glx::vec3<float>(-1.0f,-1.0f, 0.0f), glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
		{ glx::vec3<float>(1.0f,-1.0f, 1.0f), glx::vec3<float>(0, 0, 0), glx::vec2<float>(0, 1) },
		{ glx::vec3<float>(0.0f, 1.0f, 0.0f),  glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
	};

	//Alocate memory
	m_VertexBuffer.AllocateBufferObject(g_vertex_buffer_data, sizeof(drawVert) * 3, enumBuffer::STATIC_DRAW);


	//Set positions
	GLXMatrixPerspectiveRM(&m_projectionMatrix, 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	GLXMatrixRotate(&m_rotationMatrix, 260, 1.0f, 0.0f, 0.0f);
	GLXMatrixScaling(&m_modelMatrix, 1.0f, 1.0f, 1.0f);
	GLXLookAt(&m_viewMatrix, glx::vec3<float>(0, 0, 8), glx::vec3<float>(0, 0, 0), glx::vec3<float>(0, 1, 0));
	return S_OK;
}


HRESULT TestTriangle::VRender(SceneManager *pScene)
{
	if (S_OK != SceneNode::VRender(pScene))
		return E_FAIL;




	m_VertexBuffer.EnableVAO();
	m_VertexBuffer.EnableVBO();
	//m_IndexBuffer.EnableVBO();

	glDrawArrays(GL_TRIANGLES, 0, 3);
	return S_OK;
}

HRESULT TestTriangle::VOnUpdate(SceneManager *, DWORD const elapsedMs)
{


	//glx::mat4<float> mvp = m_rotationMatrix  * m_modelMatrix * m_viewMatrix * m_projectionMatrix;
	//renderProgManager.SetUniformMatrix4fv("geo.glsl", "mvp", 1, false, mvp);
	return S_OK;
}