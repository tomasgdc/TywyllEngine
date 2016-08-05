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
#ifndef _TEXTURE_H_
#define _TEXTURE_H_


/*
===============================================================================

 OpenGL texture format

===============================================================================
*/

enum class texTarget {
	GLX_TEXTURE_2D,
	GLX_TEXTURE_CUBE_MAP_POSITIVE_X,
	GLX_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GLX_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GLX_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GLX_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GLX_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum class texType {
	GLX_UNSIGNED_BYTE, 
	GLX_BYTE, 
	GLX_UNSIGNED_SHORT,
	GLX_SHORT, 
	GLX_UNSIGNED_INT, 
	GLX_INT, 
	GLX_HALF_FLOAT, 
	GLX_FLOAT,
	GLX_UNSIGNED_SHORT_5_6_5,
	GLX_UNSIGNED_SHORT_4_4_4_4,
	GLX_UNSIGNED_SHORT_5_5_5_1,
	GLX_UNSIGNED_INT_2_10_10_10_REV,
	GLX_UNSIGNED_INT_10F_11F_11F_REV,
	GLX_UNSIGNED_INT_5_9_9_9_REV,
	GLX_UNSIGNED_INT_24_8,
	GLX_FLOAT_32_UNSIGNED_INT_24_8_REV
};

enum class texFormat {
	GLX_RED,
	GLX_RED_INTEGER,
	GLX_RG,
	GLX_RG_INTEGER,
	GLX_RGB,
	GLX_RGB_INTEGER,
	GLX_RGBA,
	GLX_RGBA_INTEGER,
	GLX_DEPTH_COMPONENT,
	GLX_DEPTH_STENCIL,
	GLX_LUMINANCE_ALPHA,
	GLX_ALPHA
};


/*
===============================================================================

Texture loading

===============================================================================
*/
class TYWRENDERER_API Texture2D
{
public:
				Texture2D();
				~Texture2D();

				//Loads texture data from specified file
				Texture2D(std::string name, std::string path);

	GLuint		getId() const { return m_id; }
	int32_t	getWidth() const { return m_width; }
	int32_t	getHeight() const { return m_height; }
	std::string getName() const { return m_name; }
	std::string getPath() const { return m_path; }
	bool		IsLoaded() const { return m_loaded; }

				//Loads texture data from specified file
	void		LoadTextureFromFile(std::string name, std::string path);

				//Deletes image data loaded from file
	void		DeleteFileData();

				//Supply the needed data to glTexture2D
	void		GenerateTexture(uint8_t*  buffer, uint32_t width, uint32_t height, texFormat format);

				//Uses loaded data in class and generates from it texture id
	void		GenerateTexture(texFormat format);
				
				//Deletes data from GPU
	void		Clear();
private:
				//calls glTexImage2D with appropriate texture format
	void		TexImage2D(uint8_t*  buffer, uint32_t width, uint32_t height, texFormat format);

	GLuint		m_id;
	int32_t	m_width;
	int32_t	m_height;
	std::string m_name;
	std::string m_path;
	uint8_t*	m_image;
	bool		m_loaded;
};
#endif
