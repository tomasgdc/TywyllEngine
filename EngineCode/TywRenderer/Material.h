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
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

//forward declared
#include "OpenGL\Texture2D.h"


typedef struct TYWRENDERER_API _GLXMATERIAL
{
	glx::vec4<float> color;
	glx::vec4<float> diffuse;
	glx::vec4<float> ambient;
	glx::vec4<float> specular;
	glx::vec4<float> emmisive;
	float power;
}GLXMATERIAL;


class TYWRENDERER_API Material
{
public:
	Material();
	Material(std::string name, std::string path = "./");
	~Material();

				//Deletes texture2D class data
	void		Clear();

				//sets texture data via memcpy
	void		setLighting(GLXMATERIAL* material);

				//sets texture data via memcpy if copy is true
				//if copy false, then it just copy the location of the data
	void		setTexture(Texture2D* texture, bool copy);

	Texture2D*    getTexture() const { return m_texture; }
	GLXMATERIAL*  getLighting()  { return static_cast<GLXMATERIAL*> (&m_lighting); }

				  //returns texture width
	unsigned long getWidth() const;

				  //returns texutre height
	unsigned long getHeight() const;


	void SetAlpha(const float alpha) { m_lighting.diffuse.w = alpha; }
	bool HasAlpha() const { return GetAlpha() != 1.0f; }
	float GetAlpha() const { return m_lighting.diffuse.w; }
private:
	Texture2D*		m_texture;
	GLXMATERIAL		m_lighting;
};
#endif
