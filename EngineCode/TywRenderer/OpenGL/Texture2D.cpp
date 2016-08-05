//Copyright Tomas Mikalauskas. All rights reserved.
//Contact ttomas.mikalauskas@gmail.com
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>


//external
#include <SOIL2\SOIL2.h>

//Renderer Includes
#include "Texture2D.h"
#include "GLRenderer.h"




/*
======================
Texture2D
======================
*/
Texture2D::Texture2D() 
	:m_width(0), 
	m_height(0), 
	m_id(0), 
	m_image(nullptr), 
	m_loaded(false) 
{

}

/*
======================
Texture2D
======================
*/
Texture2D::Texture2D(std::string name, std::string path):
	m_width(0), 
	m_height(0), 
	m_id(0), 
	m_image(nullptr),
	m_loaded(false)
{
	LoadTextureFromFile(name, path);
}

/*
======================
DeleteFileData
======================
*/
void Texture2D::DeleteFileData() {
	SAFE_DELETE_ARRAY(m_image);
}

/*
======================
LoadTextureFromFile
======================
*/
void Texture2D::LoadTextureFromFile(std::string name, std::string path){
	if (m_loaded)
	{
		DeleteFileData();
	}

	m_image = SOIL_load_image((path+name).c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
	if (!m_image) 
	{
		g_RendGL.LogStrv("ERROR: Texture2D::LoadTextureFromFile -> could not load %s \n", name.c_str());
		m_loaded = false;
		return;
	}
	m_name = name;
	m_path = path;
	m_loaded = true;
}


/*
======================
TexImage2D
======================
*/
void Texture2D::TexImage2D(uint8_t*  buffer, uint32_t width, uint32_t height, texFormat format) {
	GLenum m_format(GL_RGB);

	switch (format)
	{
	case texFormat::GLX_ALPHA:
		m_format = GL_ALPHA;
		break;
	case texFormat::GLX_DEPTH_COMPONENT:
		m_format = GL_DEPTH_COMPONENT;
		break;
	case texFormat::GLX_DEPTH_STENCIL:
		m_format = GL_DEPTH_STENCIL;
		break;
	case texFormat::GLX_LUMINANCE_ALPHA:
		m_format = GL_LUMINANCE_ALPHA;
		break;
	case texFormat::GLX_RED:
		m_format = GL_RED;
		break;
	case texFormat::GLX_RED_INTEGER:
		m_format = GL_RED_INTEGER;
		break;
	case texFormat::GLX_RG:
		m_format = GL_RG;
		break;
	case texFormat::GLX_RGB:
		m_format = GL_RGB;
		break;
	case texFormat::GLX_RGBA:
		m_format = GL_RGBA;
		break;
	}

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		m_format,
		width,
		height,
		0,
		m_format,
		GL_UNSIGNED_BYTE,
		buffer
		);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Match texture alignement
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

/*
======================
GenerateTexture
======================
*/
void Texture2D::GenerateTexture(texFormat format) {
	if (m_image == nullptr)
	{
		return;
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	TexImage2D(m_image, m_width, m_height, format);
}


/*
======================
GenerateTexture
======================
*/
void Texture2D::GenerateTexture(uint8_t*  buffer, uint32_t width, uint32_t height, texFormat format) {
	if (buffer == nullptr) {
		return;
	}
	//check memory budget limits
	//no code yet

	
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
//	engine->Sys_Printf("Used %i\r\n", m_id);
	TexImage2D(buffer, width, height, format);
}

/*
======================
Clear
======================
*/
void Texture2D::Clear() {
	if (m_id != 0) {
		glDeleteTextures(1, &m_id);
	}
}

/*
======================
~Texture2D
======================
*/
Texture2D::~Texture2D() {
	//It's not going to work for font loading because each time you load to gpu data it
	//increases m_id to m_id += 1 and then it runs destructor 
	//and deletes your data once font class goes out of scope
	//which leads m_id go to 0 :( for font generation (same rule for other shits).
	//This is why my font texture was brick.jpg texture
	//because it was deleted and m_id for fonts was always 1. 
	//To m_id = 1 was loaded brick.jpg and my font always had id = 1
	//took me 6 hours to find this fucker (THAT RAGE THOUGH)
	//BE CAREFULL WITH DESTRUCTORS -> THATS WHY I HATE THEM

	//DeleteFileData();
	//Clear();
}