//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Renderer Includes
#include "Model_obj.h"

typedef struct {
	objModel_t	*model;
	objObject_t *currentObject;
}obj_t;
static obj_t objGlobal;

bool hasVer, hasNormal, hasTexCoord;

/*
===================
OBJ_ParseVertex
===================
*/
void OBJ_ParseVertex(FILE * file, std::vector<glx::vec3<float>>& v) {
	glx::vec3<float> vertex;
	fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
	v.push_back(vertex);
}

/*
===================
OBJ_ParseTexCoord
===================
*/
void OBJ_ParseTextCoord(FILE * file, std::vector<glx::vec2<float>>& v) {
	glx::vec2<float> uv;
	fscanf(file, "%f %f %f\n", &uv.x, &uv.y);
	v.push_back(uv);
}

/*
===================
OBJ_ParseNormal
===================
*/
void OBJ_ParseNormal(FILE * file, std::vector<glx::vec3<float>>& v) {
	glx::vec3<float> normal;
	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	v.push_back(normal);
}

/*
=========================
OBJ_ParseVerntexIndices
=========================
*/
void OBJ_ParseVertexIndices(FILE* file, std::vector< unsigned int >&  vertexIndices){
	unsigned int vertexIndex[3];
	fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
	vertexIndices.push_back(vertexIndex[0]-1);
	vertexIndices.push_back(vertexIndex[1]-1);
	vertexIndices.push_back(vertexIndex[2]-1);
}

/*
=========================
OBJ_ParseVertexNormalIndices
=========================
*/
void OBJ_ParseVertexNormalIndices(FILE* file,
	std::vector< unsigned int >&  vertexIndices,
	std::vector< unsigned int >&  normalIndices) {
	unsigned int vertexIndex[3], normalIndex[3];
	fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
	vertexIndices.push_back(vertexIndex[0]-1);
	vertexIndices.push_back(vertexIndex[1]-1);
	vertexIndices.push_back(vertexIndex[2]-1);
	normalIndices.push_back(normalIndex[0]-1);
	normalIndices.push_back(normalIndex[1]-1);
	normalIndices.push_back(normalIndex[2]-1);
}

/*
==============================
OBJ_ParseVertexTextureIndices
==============================
*/
void OBJ_ParseVertexTextureIndices(FILE* file,
	std::vector< unsigned int >&  vertexIndices,
	std::vector< unsigned int >&  uvIndices) {
	unsigned int vertexIndex[3], uvIndex[3];
	fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
	vertexIndices.push_back(vertexIndex[0]-1);
	vertexIndices.push_back(vertexIndex[1]-1);
	vertexIndices.push_back(vertexIndex[2]-1);
	uvIndices.push_back(uvIndex[0]-1);
	uvIndices.push_back(uvIndex[1]-1);
	uvIndices.push_back(uvIndex[2]-1);
}

/*
=====================================
OBJ_ParseVertexTextureNormalIndices
=====================================
*/
void OBJ_ParseVertexTextureNormalIndices(FILE* file,
	std::vector< unsigned int >&  vertexIndices,
	std::vector< unsigned int >&  uvIndices,
	std::vector< unsigned int >&  normalIndices) {
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
	vertexIndices.push_back(vertexIndex[0]-1);
	vertexIndices.push_back(vertexIndex[1]-1);
	vertexIndices.push_back(vertexIndex[2]-1);
	uvIndices.push_back(uvIndex[0]-1);
	uvIndices.push_back(uvIndex[1]-1);
	uvIndices.push_back(uvIndex[2]-1);
	normalIndices.push_back(normalIndex[0]-1);
	normalIndices.push_back(normalIndex[1]-1);
	normalIndices.push_back(normalIndex[2]-1);
}

/*
===================
OBJ_ParseFace
===================
*/
bool OBJ_ParseFace(FILE* file,
	std::vector< unsigned int >&  vertexIndices, 
	std::vector< unsigned int >&  uvIndices,
	std::vector< unsigned int >&  normalIndices) {

	if (hasVer && !hasNormal && !hasTexCoord) {
		OBJ_ParseVertexIndices(file, vertexIndices);
	}
	else if (hasVer && hasNormal && !hasTexCoord) {
		OBJ_ParseVertexNormalIndices(file, vertexIndices, normalIndices);
	}
	else if (hasVer && !hasNormal && hasTexCoord) {
		OBJ_ParseVertexTextureIndices(file, vertexIndices, normalIndices);
	}
	else if (hasVer && hasNormal && hasTexCoord) {
		OBJ_ParseVertexTextureNormalIndices(file, vertexIndices, uvIndices, normalIndices);
	}
	else {
		//Engine::getInstance().Sys_Printf("ERROR: OBJ_ParseFace: wrong format \r\n");
		return false;
	}
	return true;
}

/*
========================
OBJ_ParseObject
========================
*/
int OBJ_ParseObject(FILE* file, const char* objectName,
	std::vector<glx::vec3<float>>& temp_vertices,
	std::vector<glx::vec2<float>>& temp_uvs,
	std::vector<glx::vec3<float>>& temp_normals) {

	char materialName[128];
	memset(materialName, 0, sizeof(materialName));

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	int numVertices = 0, numNormals = 0, numTexCoord = 0, numFaces = 0;
	hasVer = false, hasNormal = false, hasTexCoord = false;
	int res = 0;
	while (1) {
		char lineHeader[128];
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF) { break; }
		else if (strcmp(lineHeader, "o") == 0) {
			char objectName[128];
			fscanf(file, "%s\n", objectName);
			res = OBJ_ParseObject(file, objectName, temp_vertices, temp_uvs, temp_normals);
		}
		
		if (strcmp(lineHeader, "v") == 0) {
			OBJ_ParseVertex(file, temp_vertices);
			numVertices++;
			hasVer = true;
		}
		else if ((strcmp(lineHeader, "vt") == 0)) {
			OBJ_ParseTextCoord(file, temp_uvs);
			numTexCoord++;
			hasTexCoord = true;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			OBJ_ParseNormal(file, temp_normals);
			numNormals++;
			hasNormal = true;
		}
		else if (strcmp(lineHeader, "usemtl") == 0) {
			fscanf(file, "%s\n", materialName);
		}
		else if ((strcmp(lineHeader, "f") == 0)) {
			if (!OBJ_ParseFace(file, vertexIndices, uvIndices, normalIndices)) {
				return 0;
			}
			numFaces++;
		}
	}
	//Create new object
	objObject_t *object = TYW_NEW objObject_t;
	memset(object, 0, sizeof(objObject_t));

	//get object group name and material group name
	strcpy(object->name, objectName);
	strcpy(object->mat_name, materialName);

	objGlobal.model->objects.push_back(object);
	objGlobal.currentObject = object;

	//check against nullptr
	objMesh_t* pMesh = &objGlobal.currentObject->mesh;

	//Create needed size
	pMesh->vertices = TYW_NEW glx::vec3<float>[numFaces*3];
	pMesh->normals	= TYW_NEW glx::vec3<float>[numFaces*3];
	pMesh->uvs		= TYW_NEW glx::vec2<float>[numFaces*3];
	pMesh->faces	= nullptr;

	pMesh->numVertexes	= numFaces*3;
	pMesh->numUvs		= numFaces*3 ;
	pMesh->numNormals	= numFaces*3;
	pMesh->numFaces		= numFaces;

	//DEBUG
	//Engine::getInstance().Sys_Printf("Mesh:     %s \r\n", objectName);
	//Engine::getInstance().Sys_Printf("VERTEX:	  %i \r\n", numVertices);
	///Engine::getInstance().Sys_Printf("TEXCOORD: %i \r\n", numTexCoord);
	//Engine::getInstance().Sys_Printf("NORMALS:  %i \r\n", numNormals);
	//Engine::getInstance().Sys_Printf("FACES:    %i \r\n", numFaces);
	//Engine::getInstance().Sys_Printf("\r\n");

	//Put data
	for (int i = 0; i < pMesh->numFaces*3; i++) {
			pMesh->vertices[i]	= temp_vertices[vertexIndices[i]];
			pMesh->uvs[i]		= temp_uvs[uvIndices[i]];
			pMesh->normals[i]	= temp_normals[normalIndices[i]];
	}
	return res;
}
/*
==============================
OBJ_ParseMesh
Not used
==============================
*/
int OBJ_ParseMesh(FILE* file, const char* objectName) {

	int res = 0;
	while (1) {
		char lineHeader[128];
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF) { break; }
		
		if (strcmp(lineHeader, "o") == 0) {
			char objectName[60];
			fscanf(file, "%s\n", objectName);
			//res = OBJ_ParseObject(file, objectName, temp_vertices, temp_uvs, temp_normals);
		}
	}
	return res;
}

/*
============================
OBJ_ParseNewMTL - newmtl
============================
*/
void OBJ_ParseNewMTL(FILE* file, objModel_t* model, std::string mtlName) {
	objMaterial_t* material = TYW_NEW objMaterial_t;
	
	material->map_bump[0]	= 0;
	material->map_d[0]		= 0;
	material->map_Ka[0]		= 0;
	material->map_Kd[0]		= 0;
	material->map_Ks[0]		= 0;
	material->map_Ns[0]		= 0;
	material->count			= 0;
	strcpy(material->name, mtlName.c_str());
	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF) { break; }
		else if (strcmp(lineHeader, "newmtl") == 0) {
			char mtlName[60];
			fscanf(file, "%s\n", &mtlName);
			OBJ_ParseNewMTL(file, model, mtlName);
		}
		
		if(strcmp(lineHeader, "map_Kd") == 0) {
			fscanf(file, "%s\n", &material->map_Kd);
			material->count += 1;
		}
		else if (strcmp(lineHeader, "map_Ks") == 0) {
			fscanf(file, "%s\n", &material->map_Ks);
			material->count += 1;
		}
		else if (strcmp(lineHeader, "map_Bump") == 0) {
			fscanf(file, "%s\n", &material->map_bump);
			material->count += 1;
		}
	}
	model->materials.push_back(material);
}
/*
===================
OBJ_ParseMTL   - material.txt file

map_Ka lenna.tga           # the ambient texture map
map_Kd lenna.tga           # the diffuse texture map (most of the time, it will 
						   #be the same as the ambient texture map)
map_Ks lenna.tga           # specular color texture map
map_Ns lenna_spec.tga      # specular highlight component
map_d lenna_alpha.tga      # the alpha texture map
map_bump lenna_bump.tga    # some implementations use 'map_bump' instead of 'bump' below

bump lenna_bump.tga        # bump map (which by default uses luminance channel of the image)
disp lenna_disp.tga        # displacement map
decal lenna_stencil.tga    # stencil decal texture (defaults to 'matte' channel of the image)
===================
*/
objMaterial_t* OBJ_ParseMTL(const char* fileName){
	if (objGlobal.model == nullptr) {
		objGlobal.model = TYW_NEW objModel_t;
	}
	objModel_t* model = objGlobal.model;

	FILE* file = fopen(fileName, "r");
	if (file == nullptr) {
		//Engine::getInstance().Sys_Printf("ERROR: Could not load OBJ material file %s", fileName);
		return nullptr;
	}
	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) { break; }

		if (strcmp(lineHeader, "newmtl") == 0) {
			char mtlName[60];
			fscanf(file, "%s\n", &mtlName);
			OBJ_ParseNewMTL(file, model, mtlName);
		}
	}

	//DEBUG
	for (int i = 0; i < model->materials.size(); i++) {
		objMaterial_t* mat = model->materials[i];
		//Engine::getInstance().Sys_Printf("Material name: %s \r\n", mat->name);
		//Engine::getInstance().Sys_Printf("map_Kd:	   %s  \r\n", mat->map_Kd);
		//Engine::getInstance().Sys_Printf("map_Ks:    %s  \r\n", mat->map_Ks);
		//Engine::getInstance().Sys_Printf("map_Bump:  %s  \r\n", mat->map_bump);
		//Engine::getInstance().Sys_Printf("\r\n");
	}
	return nullptr;
}

/*
===================
OBJ_Parse
===================
*/
objModel_t* OBJ_Parse(FILE* file, std::string& filePath) {
	memset(&objGlobal, 0, sizeof(objGlobal));

	std::vector<glx::vec3<float>> temp_vertices;
	std::vector<glx::vec2<float>> temp_uvs;
	std::vector<glx::vec3<float>> temp_normals;

	objGlobal.currentObject = nullptr;
	objGlobal.model = nullptr;
	objGlobal.model = TYW_NEW objModel_t;
	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF || res == 0) { break; }

		if (strcmp(lineHeader, "mtllib") == 0) {
			char fileName[60];
			fscanf(file, "%s\n", fileName);
			OBJ_ParseMTL((filePath+fileName).c_str());
		}
		else if (strcmp(lineHeader, "o") == 0) {
			char objectName[60];
			fscanf(file, "%s\n", objectName);
			res = OBJ_ParseObject(file, objectName, temp_vertices, temp_uvs, temp_normals);
		}
	}
	return objGlobal.model;
}


/*
===================
OBJ_Load
===================
*/
objModel_t* OBJ_Load(std::string fileName, std::string filePath) {
	objModel_t* obj = nullptr;
	FILE* file = fopen((filePath+fileName).c_str(), "r");
	if (!file) {
		return nullptr;
	}
	obj = OBJ_Parse(file, filePath);
	fclose(file);
	return obj;
}


/*
===================
OBJ_Free
===================
*/
void OBJ_Free(objModel_t* wav){
	int					i;
	objObject_t			*obj;
	objMesh_t			*mesh;
	objMaterial_t		*material;
	if (!wav) {
		return;
	}
	for (int i = 0; i < wav->objects.size(); i++) {
		obj = wav->objects[i];
		
		mesh = &obj->mesh;
		SAFE_DELETE_ARRAY(mesh->vertices);
		SAFE_DELETE_ARRAY(mesh->uvs);
		SAFE_DELETE_ARRAY(mesh->normals);
		SAFE_DELETE_ARRAY(mesh->faces);
		SAFE_DELETE(obj);
	}
	wav->objects.clear();

	for (int i = 0; i < wav->materials.size(); i++) {
		material = wav->materials[i];
		SAFE_DELETE(material);
	}
	wav->materials.clear();
	SAFE_DELETE(wav);
}