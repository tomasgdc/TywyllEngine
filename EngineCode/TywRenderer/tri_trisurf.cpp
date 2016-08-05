//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\VertData.h>

//Renderer Includes
#include "Model.h"
#include "GLRenderer.h"


srfTriangles_t* R_AllocStaticTriSurf() 
{
	srfTriangles_t* tri = TYW_NEW srfTriangles_t;
	return tri;
}

void R_AllocStaticTriSurfVerts(srfTriangles_t *tri, int numVerts) 
{
	if (!tri)return;
	tri->numVerts = numVerts;
	tri->verts = TYW_NEW drawVert[numVerts];
}
void	R_AllocStaticTriSurfIndexes(srfTriangles_t *tri, int numIndexes) 
{
	if (!tri)return;
	tri->numIndexes = numIndexes;
	tri->indexes = TYW_NEW uint16_t[numIndexes]; //use 16bit alloc for indixes
}

void	R_FreeStaticTriSurfSilIndexes(srfTriangles_t *tri) 
{
	if (!tri)return;
	SAFE_DELETE_ARRAY(tri->indexes);
}

void	R_FreeStaticTriSurf(srfTriangles_t *tri) 
{
	if (tri == nullptr)return;

	SAFE_DELETE_ARRAY(tri->verts);
	SAFE_DELETE_ARRAY(tri->indexes);
	SAFE_DELETE(tri);
}

void	R_FreeStaticTriSurfVerts(srfTriangles_t *tri) 
{
	if (!tri)return;
	SAFE_DELETE_ARRAY(tri->verts);
}

void R_CreateStaticBuffersForTri(srfTriangles_t & tri) {

}