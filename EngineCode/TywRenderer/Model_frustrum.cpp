#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\math\GLXConstants.h>


//Renderer Includes
#include "Model.h"


//
// Frustum::Frustum					- Chapter 14, page 477
//
Frustum::Frustum()
{
	m_Fov = PI / 4.0f;		// default field of view is 90 degrees
	m_Aspect = 1.0f;			// default aspect ratio is 1:1
	m_Near = 1.0f;				// default near clip plane is 1m away from the camera
	m_Far = 1000.0f;				// default near clip plane is 100m away from the camera
}


//
// Frustum::Inside					- Chapter 14, page 477
//
bool Frustum::Inside(const glx::vec3<float> &point) const
{
	for (int i = 0; i<NumPlanes; ++i)
	{
		if (!m_Planes[i].Inside(point))
			return false;
	}

	return true;
}


//
// Frustum::Inside					- Chapter 14, page 477
//
bool Frustum::Inside(const glx::vec3<float> &point, const float radius) const
{
	for (int i = 0; i < NumPlanes; ++i)
	{
		if (!m_Planes[i].Inside(point, radius))
			return false;
	}

	// otherwise we are fully in view
	return(true);
}

//
// Frustum::Init					- Chapter 14, page 477
//
void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip)
{
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;

	float tanFovOver2 = (float)tan(m_Fov / 2.0f);
//	glx::vec3<float> nearRight = (m_Near * tanFovOver2) * m_Aspect;// *g_Right;
//	glx::vec3<float> farRight = (m_Far * tanFovOver2) * m_Aspect;// *g_Right;
//	glx::vec3<float> nearUp = (m_Near * tanFovOver2);// *g_Up;
//	glx::vec3<float> farUp = (m_Far * tanFovOver2);//  *g_Up;

	// points start in the upper right and go around clockwise
	/*
	m_NearClip[0] = (m_Near * g_Forward) - nearRight + nearUp;
	m_NearClip[1] = (m_Near * g_Forward) + nearRight + nearUp;
	m_NearClip[2] = (m_Near * g_Forward) + nearRight - nearUp;
	m_NearClip[3] = (m_Near * g_Forward) - nearRight - nearUp;

	m_FarClip[0] = (m_Far * g_Forward) - farRight + farUp;
	m_FarClip[1] = (m_Far * g_Forward) + farRight + farUp;
	m_FarClip[2] = (m_Far * g_Forward) + farRight - farUp;
	m_FarClip[3] = (m_Far * g_Forward) - farRight - farUp;

	// now we have all eight points. Time to construct 6 planes.
	// the normals point away from you if you use counter clockwise verts.

	glx::vec3<float> origin(0.0f, 0.0f, 0.0f);
	m_Planes[Near].Init(m_NearClip[2], m_NearClip[1], m_NearClip[0]);
	m_Planes[Far].Init(m_FarClip[0], m_FarClip[1], m_FarClip[2]);
	m_Planes[Right].Init(m_FarClip[2], m_FarClip[1], origin);
	m_Planes[Top].Init(m_FarClip[1], m_FarClip[0], origin);
	m_Planes[Left].Init(m_FarClip[0], m_FarClip[3], origin);
	m_Planes[Bottom].Init(m_FarClip[3], m_FarClip[2], origin);
	*/
}



//
// Frustum::Render					- not described in the 4th edition
//
void Frustum::Render()
{
	//D3D9Vertex_Colored verts[24];
	/*
	for (int i = 0; i<8; ++i)
	{
		verts[i].color = g_White;
	}

	for (int i = 0; i<8; ++i)
	{
		verts[i + 8].color = g_Red;
	}

	for (int i = 0; i<8; ++i)
	{
		verts[i + 16].color = g_Blue;
	}
	

	// Draw the near clip plane
	verts[0].position = m_NearClip[0];	verts[1].position = m_NearClip[1];
	verts[2].position = m_NearClip[1];	verts[3].position = m_NearClip[2];
	verts[4].position = m_NearClip[2];	verts[5].position = m_NearClip[3];
	verts[6].position = m_NearClip[3];	verts[7].position = m_NearClip[0];

	// Draw the far clip plane
	verts[8].position = m_FarClip[0];	verts[9].position = m_FarClip[1];
	verts[10].position = m_FarClip[1];	verts[11].position = m_FarClip[2];
	verts[12].position = m_FarClip[2];	verts[13].position = m_FarClip[3];
	verts[14].position = m_FarClip[3];	verts[15].position = m_FarClip[0];

	// Draw the edges between the near and far clip plane
	verts[16].position = m_NearClip[0];	verts[17].position = m_FarClip[0];
	verts[18].position = m_NearClip[1];	verts[19].position = m_FarClip[1];
	verts[20].position = m_NearClip[2];	verts[21].position = m_FarClip[2];
	verts[22].position = m_NearClip[3];	verts[23].position = m_FarClip[3];

	
	DWORD oldLightMode;
	DXUTGetD3D9Device()->GetRenderState(D3DRS_LIGHTING, &oldLightMode);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);

	DXUTGetD3D9Device()->SetFVF(D3D9Vertex_Colored::FVF);
	DXUTGetD3D9Device()->DrawPrimitiveUP(D3DPT_LINELIST, 12, verts, sizeof(D3D9Vertex_Colored));

	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, oldLightMode);
	*/
}
