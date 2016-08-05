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
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\geometry\JointTransform.h>

//Renderer Includes
#include "Model_local.h"


/*
========================
InstantiateDynamicModel
========================
*/
RenderModel *	RenderModelSprite::InstantiateDynamicModel()
{
	RenderModelStatic* staticModel;
	srfTriangles_t *tri;

	//alloc 
	staticModel = TYW_NEW RenderModelStatic;

	//alloc space
	tri = staticModel->AllocSurfaceTriangles(6, 0);

	//1 triangle
	tri->verts[0].Clear();
	tri->verts[0].SetVertex(0.0f, 0.0f, 0.0f);
	tri->verts[0].SetTexCoords(0.0f, 0.0f);

	tri->verts[1].Clear();
	tri->verts[1].SetVertex(0.0f, 1.0f, 0.0f);
	tri->verts[1].SetTexCoords(0.0f, 1.0f);

	tri->verts[2].Clear();
	tri->verts[2].SetVertex(1.0f, 0.0f, 0.0f);
	tri->verts[2].SetTexCoords(1.0f, 0.0f);

	//2 triangle
	tri->verts[3].Clear();
	tri->verts[3].SetVertex(1.0f, 0.0f, 0.0f);
	tri->verts[3].SetTexCoords(1.0f, 0.0f);

	tri->verts[4].Clear();
	tri->verts[4].SetVertex(0.0f, 1.0f, 0.0f);
	tri->verts[4].SetTexCoords(0.0f, 1.0f);

	tri->verts[5].Clear();
	tri->verts[5].SetVertex(1.0f, 1.0f, 0.0f);
	tri->verts[5].SetTexCoords(1.0f, 1.0f);

	//memcpy
	staticModel->Memcpy(tri, sizeof(srfTriangles_t));
	return staticModel;



}