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
#ifndef _DRAW_VERT_DATA_H_
#define _DRAW_VERT_DATA_H_

class drawVert
{
public:
	drawVert(glx::vec3<float> v, glx::vec3<float> n, glx::vec2<float> t);
	drawVert(glx::vec3<float>& v, glx::vec3<float>& n, glx::vec2<float>& t);
	drawVert();

	glx::vec3<float> vertex; //12 bytes
	glx::vec3<float> normal; //12 bytes
	glx::vec2<float> tex;    //8 bytes

	void Clear();
	void SetVertex(float x, float y, float z);
	void SetNormal(float x, float y, float z);
	void SetTexCoords(float x, float y);
};


inline drawVert::drawVert(glx::vec3<float> v, glx::vec3<float> n, glx::vec2<float> t):
	vertex(v), normal(n), tex(t)
{

}


inline drawVert::drawVert(glx::vec3<float>& v, glx::vec3<float>& n, glx::vec2<float>& t):
	vertex(v), normal(n), tex(t)
{

}

inline drawVert::drawVert():
	vertex(0.0f, 0.0f, 0.0f),
	normal(0.0f, 0.0f, 0.0f),
	tex(0.0f, 0.0f)
{

}


inline void drawVert::Clear()
{
	this->vertex.Clear();
	this->normal.Clear();
	this->tex.Clear();
}


inline void drawVert::SetVertex(float x, float y, float z)
{
	this->vertex = glx::vec3<float>(x, y, z);
}


inline void drawVert::SetNormal(float x, float y, float z)
{
	this->vertex = glx::vec3<float>(x, y, z);
}

inline void drawVert::SetTexCoords(float x, float y)
{
	this->tex = glx::vec2<float>(x, y);
}


#endif