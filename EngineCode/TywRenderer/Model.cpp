//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>

//Renderer Includes
#include "OpenGL\BufferObject.h"
#include "Model.h"
#include "Model_local.h"
#include "Image.h"
#include "Model_obj.h"
#include "Material.h"
#include "VertexCache.h"
#include "GLRenderer.h"



/*
=========================
RenderModelStatic
=========================
*/
RenderModelStatic::RenderModelStatic() {

}

/*
=========================
InitFromFile
=========================
*/
void RenderModelStatic::InitFromFile(std::string fileName, std::string filePath) {
	bool loaded = false;

	loaded = OBJLoad(fileName, filePath);
	if (!loaded) {
	//	Engine::getInstance().Sys_Printf("Could not load model: %s", fileName.c_str());
	}
}

/*
=========================
OBJLoad
=========================
*/
bool RenderModelStatic::OBJLoad(std::string& fileName, std::string& filePath) {
	//DEBUG
	//Engine::getInstance().Sys_Printf("Loading OBJ model: %s \r\n", fileName.c_str());

	objModel_t* obj;
	obj = OBJ_Load(fileName, filePath);
	if (obj == nullptr) {
		return false;
	}
	ConvertOBJToModelSurfaces(obj);
	OBJ_Free(obj);
	return true;
}

/*
=========================
ConvertOBJToModelSuraces
=========================
*/
bool RenderModelStatic::ConvertOBJToModelSurfaces(const struct objModel_a* obj) {
	int					objectNum;
	int					materialNum;
	srfTriangles_t *	tri;
	objObject_t*		object;
	objMaterial_t*		material;
	objMesh_t*			mesh;
	modelSurface_t		surf, *modelSurf;

	
	//Loads image if it was not stored in globalImage
	for (materialNum = 0; materialNum < obj->materials.size(); materialNum++) {
		material = obj->materials[materialNum];

		if (strlen(material->map_bump) != 0) {
			globalImage->GetImage(material->map_bump);
		}
		if (strlen(material->map_d) != 0) {
			globalImage->GetImage(material->map_d);
		}
		if (strlen(material->map_Ka) != 0) {
			globalImage->GetImage(material->map_Ka);
		}
		if (strlen(material->map_Kd) != 0) {
			globalImage->GetImage(material->map_Kd);
		}
		if (strlen(material->map_Ks) != 0) {
			globalImage->GetImage(material->map_Ks);
		}
		if (strlen(material->map_Ns) != 0) {
			globalImage->GetImage(material->map_Ns);
		}
		Material* mat = TYW_NEW Material;
		mat->setTexture(globalImage->GetImage(material->map_Kd), false);
		m_material.insert(std::pair<std::string, Material*>(material->name, mat));
	}

	
	//Converts OBJ mesh data to modelSurface_t data
	for (objectNum = 0; objectNum < obj->objects.size(); objectNum++) {
		surfaces.push_back(surf);
		object = obj->objects[objectNum];
		mesh = &object->mesh;
		
		
		tri = nullptr;
		tri = R_AllocStaticTriSurf();
		tri->numVerts = 0;
		tri->numIndexes = 0;
		tri->indexes = nullptr;

		R_AllocStaticTriSurfVerts(tri, mesh->numFaces*3);
		for (int i = 0; i < mesh->numFaces*3; i++) {
			tri->verts[i].Clear();
			tri->verts[i].vertex = mesh->vertices[i];
			tri->verts[i].normal = mesh->normals[i];
			tri->verts[i].tex	 = mesh->uvs[i];
		}
		modelSurf = &this->surfaces[objectNum];
		modelSurf->geometry = tri;
		modelSurf->material = nullptr;
		it = m_material.find(object->mat_name);
		if (it != m_material.end()) 
		{ 
			modelSurf->material = it->second; 
		//	Engine::getInstance().Sys_Printf("Found %s\r\n", object->mat_name);
		}
	}
	return true;
}

/*
=========================
addSurface
=========================
*/
void RenderModelStatic::addSurface(modelSurface_t& surface) {
	surfaces.push_back(surface);
}

/*
=========================
LoadModel
=========================
*/
void RenderModelStatic::LoadModel() {

}

/*
=========================
AllocSurfaceTriangles
=========================
*/
srfTriangles_t * RenderModelStatic::AllocSurfaceTriangles(int numVerts, int numIndexes) const{
	srfTriangles_t* tri = R_AllocStaticTriSurf();
	R_AllocStaticTriSurfVerts(tri, 6);
	return tri;
}

/*
=========================
InstantiateDynamicModel
=========================
*/
RenderModel *	RenderModelStatic::InstantiateDynamicModel() {
	//Engine::getInstance().Sys_Error("ERROR: InstantiateDynamicModel -> called on static model %s\r\n", name.c_str());
	return nullptr;
}

/*
=========================
setName
=========================
*/
void RenderModelStatic::setName(std::string name) {
	this->name = name;
}


/*
=========================
Memcpy
=========================
*/
void RenderModelStatic::Memcpy(srfTriangles_t * tri, size_t size){
	//memcpy(m_geometry, tri, size);
}

/*
=========================
getName
=========================
*/
const char	* RenderModelStatic::getName() const {
	return name.c_str();
}

/*
=========================
getSize
=========================
*/
int RenderModelStatic::getSize() const{
	return 0;
}

/*
=========================
FreeSurfaceTriangles
=========================
*/
void RenderModelStatic::FreeSurfaceTriangles(srfTriangles_t *tris){
	R_FreeStaticTriSurf(tris);
}


/*
=========================
Clear
=========================
*/
void RenderModelStatic::Clear() {
	std::vector<modelSurface_t>::iterator			m_it;
	for (m_it = surfaces.begin(); m_it != surfaces.end(); ++m_it) {
		FreeSurfaceTriangles(m_it->geometry);
	}
	surfaces.clear();

	for (it = m_material.begin(); it != m_material.end(); ++it) {
		it->second->Clear();
		SAFE_DELETE(it->second);
	}
	m_material.clear();
}


/*
=========================
setMaterial
=========================
*/
void RenderModelStatic::setMaterial(std::string name, Material* mat) {
	m_material.insert(std::map<std::string, Material*>::value_type(name, mat));
}