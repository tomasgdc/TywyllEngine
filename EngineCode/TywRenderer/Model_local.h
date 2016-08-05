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
#ifndef _MODEL_LOCAL_H_
#define _MODEL_LOCAL_H_
#include "Model.h"


//forward declarationm
#include <TywLib\geometry\JointTransform.h>


/*
================================================================================

RenderModelStatic

================================================================================
*/
class TYWRENDERER_API RenderModelStatic: public RenderModel
{
public:
								RenderModelStatic();
	virtual						~RenderModelStatic() {}

	virtual void				InitFromFile(std::string fileName, std::string filePath);
	virtual void				LoadModel();
	virtual srfTriangles_t *	AllocSurfaceTriangles(int numVerts, int numIndexes) const;
	virtual void				FreeSurfaceTriangles(srfTriangles_t *tris);
	virtual RenderModel *		InstantiateDynamicModel();
	void						Memcpy(srfTriangles_t * tri, size_t size);

	bool						OBJLoad(std::string& fileName, std::string& filePath);
	bool						ConvertOBJToModelSurfaces(const struct objModel_a* obj);

	virtual void				Clear();
	virtual const char	*		getName() const;
	virtual int					getSize() const;
	void						setName(std::string name);
	void						setMaterial(std::string name, Material* mat);
	void						addSurface(modelSurface_t& surface);
public:
	std::map<std::string, Material*>				m_material;
	std::map<std::string, Material*>::iterator		it;

	std::string										name;
	std::vector<modelSurface_t>						surfaces;
};

/*
===============================================================================

MD5 animated model

===============================================================================
*/




struct triangleIndex_t
{
	uint32_t					indices[3];
};

struct vertexWeight_t
{
	uint32_t					jointId;
	glx::vec3<float>			pos;
	float						jointWeight;
};


struct vertIndex_t
{
	uint32_t					index;
	uint32_t					firstWeightForVertex;
	uint32_t					numWeightsForVertex;
	glx::vec2<float>			texCoord;
};


class TYWRENDERER_API MD5Mesh 
{
	
	friend class				RenderModelMD5;

public:
	MD5Mesh();
	~MD5Mesh();

	void						ParseMesh(FILE* file, int numJoints, std::vector<JointMat>& joints);

	int							NumVerts() const { return numVerts; }
	int							NumTris() const { return numTris; }

	void						UpdateMesh(const MD5Mesh *mesh, std::vector<JointQuat>& joints, const	JointMat *entJointsInverted, deformInfo_t *surf);
	//void						CalculateBounds(const idJointMat * entJoints, idBounds & bounds) const;
	int							NearestJoint(int a, int b, int c) const;

public:
	std::vector<vertIndex_t>	verts;
	std::vector<vertexWeight_t>  weight;
	//std::vector<triangleIndex_t> tri;
	std::vector<GLuint> tri;

	uint32_t					numVerts;			// number of vertices
	uint32_t					numTris;			// number of triangles
	uint32_t					numMeshJoints;		// number of mesh joints
	uint32_t					surfaceNum;			// number of the static surface created for this mesh
	float						maxJointVertDist;	// maximum distance a vertex is separated from a joint
	deformInfo_t *				deformInfo;			// used to create srfTriangles_t from base frames and new vertexes
	int8_t *					meshJoints;			// the joints used by this mesh
	Material *					shader;				// material applied to mesh
};

class TYWRENDERER_API RenderModelMD5 : public RenderModelStatic 
{
public:
	virtual void				InitFromFile(std::string fileName, std::string filePath);
	//virtual bool				LoadBinaryModel(idFile * file, const ID_TIME_T sourceTimeStamp);
	//virtual void				WriteBinaryModel(idFile * file, ID_TIME_T *_timeStamp = NULL) const;
	//virtual dynamicModel_t	IsDynamicModel() const;
	//virtual idBounds			Bounds(const struct renderEntity_s *ent) const;
	//virtual void				Print() const;
	//virtual void				List() const;
	//virtual void				TouchData();
	//virtual void				PurgeModel();
	//virtual void				LoadModel();
	//virtual int					Memory() const;
	//virtual RenderModel *		InstantiateDynamicModel(const struct renderEntity_s *ent, const viewDef_t *view, idRenderModel *cachedModel);
	//virtual int					NumJoints() const;
	//virtual const MD5Joint *	GetJoints() const;
	//virtual jointHandle_t		GetJointHandle(const char *name) const;
	//virtual const char *		GetJointName(jointHandle_t handle) const;
	//virtual const idJointQuat *	GetDefaultPose() const;
	//virtual int					NearestJoint(int surfaceNum, int a, int b, int c) const;

	//virtual bool				SupportsBinaryModel() { return true; }

public:
	std::vector<MD5Joint>	joints;
	std::vector<JointQuat>	defaultPose;
	std::vector<MD5Mesh>	meshes;
	

	//void						DrawJoints(const renderEntity_t *ent, const viewDef_t *view) const;
	bool						ParseJoint(FILE* ptrfile, MD5Joint& joint, JointQuat& pose);
};

/*
================================================================================

RenderModelSprite

================================================================================
*/
class TYWRENDERER_API RenderModelSprite: public RenderModel 
{
public:
	virtual RenderModel *		InstantiateDynamicModel();

};
#endif


