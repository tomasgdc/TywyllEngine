//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\geometry\JointTransform.h>


//Renderer Includes
#include "OpenGL\Texture2D.h"
#include "Material.h"


/*
========================
Material
========================
*/
Material::Material():m_texture(nullptr) {

}

/*
========================
Material
========================
*/
Material::Material(std::string name, std::string path):m_texture(nullptr){
	m_texture = TYW_NEW Texture2D(name, path);
}

/*
========================
getWidth
========================
*/
unsigned long Material::getWidth() const {
	if (!m_texture)return 0;
	return m_texture->getWidth();
}

/*
========================
getHeight
========================
*/
unsigned long Material::getHeight() const {
	if (!m_texture)return 0;
	return m_texture->getHeight();
}

/*
========================
setLighting

maybe not the best name.....
kinda confusing
========================
*/
void Material::setLighting(GLXMATERIAL* material) {
	memcpy(&m_lighting, material, sizeof(material));
}

/*
========================
setTexture
========================
*/
void Material::setTexture(Texture2D* texture, bool copy) {
	if (texture == nullptr) { return; }

	if (copy) 
	{
		memcpy(m_texture, texture, sizeof(texture));
	}
	else 
	{
		m_texture = texture;
	}
}

/*
========================
Clear
========================
*/
void Material::Clear() {
	if (!m_texture)return;

	m_texture->DeleteFileData();
	m_texture->Clear();
	SAFE_DELETE(m_texture);
}

/*
========================
~Material
========================
*/
Material::~Material() {
	//Clear();
}