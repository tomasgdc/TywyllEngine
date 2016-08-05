/* ============================================================================
* Tywyl Engine
* Platform:      Windows
* WWW:
* ----------------------------------------------------------------------------
* Copyright 2015 Tomas Mikalauskas. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY TOMAS MIKALAUSKAS ''AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL TOMAS MIKALAUSKAS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are
* those of the authors and should not be interpreted as representing official
* policies, either expressed or implied, of Tomas Mikalauskas.

DISCLAIMER
The engine design is based on Doom3 BFG engine
https://github.com/id-Software/DOOM-3-BFG.
A lot of tweaks maded to suit my needs.
Tywyll game engine design and functionality will be changed with time.
============================================================================
*/
#ifndef _MODEL_H_
#define _MODEL_H_

//forwad declared
class Material;
class drawVert;


// our only drawing geometry type
struct TYWRENDERER_API srfTriangles_t 
{
	int					numVerts;		//number of vertices
	drawVert*			verts;			//vert, normal, tex

	int					numIndexes;		//number of indixes
	uint16_t*			indexes;		//vertex indices
};

struct TYWRENDERER_API modelSurface_t 
{
	int					id;
	Material*			material;
	srfTriangles_t*		geometry;
};

struct TYWRENDERER_API MD5Joint {
	char								name[256];
	int									parentID;
};

// deformable meshes precalculate as much as possible from a base frame, then generate
// complete srfTriangles_t from just a new set of vertexes
struct TYWRENDERER_API deformInfo_t 
{
	int					numSourceVerts;

	// numOutputVerts may be smaller if the input had duplicated or degenerate triangles
	// it will often be larger if the input had mirrored texture seams that needed
	// to be busted for proper tangent spaces
	int					numOutputVerts;
	drawVert *			verts;

	int					numIndexes;
	uint16_t *			indexes;

	uint16_t *			silIndexes;				// indexes changed to be the first vertex with same XYZ, ignoring normal and texcoords

	int					numMirroredVerts;		// this many verts at the end of the vert list are tangent mirrors
	int *				mirroredVerts;			// tri->mirroredVerts[0] is the mirror of tri->numVerts - tri->numMirroredVerts + 0

	int					numDupVerts;			// number of duplicate vertexes
	int *				dupVerts;				// pairs of the number of the first vertex and the number of the duplicate vertex
};

class TYWRENDERER_API RenderModel 
{
public:
	virtual ~RenderModel() {};

	// used for initial loads, reloadModel, and reloading the data of purged models
	// Upon exit, the model will absolutely be valid, but possibly as a default model
	virtual void				LoadModel() = 0;

	//Loads only static models
	virtual void				InitFromFile(std::string fileName, std::string filePath) = 0;


	//Allocate triangle data
	virtual srfTriangles_t *	AllocSurfaceTriangles(int numVerts, int numIndexes) const = 0;

	// Frees surfaces triangles.
	virtual void				FreeSurfaceTriangles(srfTriangles_t *tris) = 0;

	// returns a static model
	virtual RenderModel *		InstantiateDynamicModel() = 0;

	// returns the name of the model
	virtual const char	*		getName() const = 0;

	// reports the amount of memory (roughly) consumed by the model
	virtual int					getSize() const = 0;	

	//Deletes any data that was stored in class. 
	//Each derived class can have different clearing implementation
	virtual void				Clear() = 0;
};




/*
================================================================================

Plane

================================================================================
*/
class TYWRENDERER_API Plane
{
public:
	inline void Normalize();

	// normal faces away from you if you send in verts in counter clockwise order....
	inline void Init(const glx::vec3<float> &p0, const glx::vec3<float> &p1, const glx::vec3<float> &p2);
	bool Inside(const glx::vec3<float> &point, const float radius) const;
	bool Inside(const glx::vec3<float> &point) const;
};

inline void Plane::Normalize()
{
	float mag;
	//mag = sqrt(a * a + b * b + c * c);
	//a = a / mag;
	//b = b / mag;
	//c = c / mag;
	//d = d / mag;
}

inline void Plane::Init(const glx::vec3<float> &p0, const glx::vec3<float> &p1, const glx::vec3<float> &p2)
{
	//D3DXPlaneFromPoints(this, &p0, &p1, &p2);
	Normalize();
}


/*
================================================================================

Frustrum

================================================================================
*/
class TYWRENDERER_API Frustum
{
public:
	enum Side { Near, Far, Top, Right, Bottom, Left, NumPlanes };

	Plane m_Planes[NumPlanes];	// planes of the frusum in camera space
	glx::vec3<float> m_NearClip[4];			// verts of the near clip plane in camera space
	glx::vec3<float> m_FarClip[4];			// verts of the far clip plane in camera space

	float m_Fov;				// field of view in radians
	float m_Aspect;				// aspect ratio - width divided by height
	float m_Near;				// near clipping distance
	float m_Far;				// far clipping distance

public:
	Frustum();

	bool Inside(const glx::vec3<float> &point) const;
	bool Inside(const glx::vec3<float> &point, const float radius) const;
	const Plane &Get(Side side) { return m_Planes[side]; }
	void SetFOV(float fov) { m_Fov = fov; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetAspect(float aspect) { m_Aspect = aspect; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetNear(float nearClip) { m_Near = nearClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetFar(float farClip) { m_Far = farClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void Init(const float fov, const float aspect, const float near, const float far);

	void Render();
};
#endif