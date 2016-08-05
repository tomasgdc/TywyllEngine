//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>


//Renderer Includes
#include "OpenGL\Texture2D.h"
#include "Image.h"



ImageManager imageManager;
ImageManager* globalImage = &imageManager;

Texture2D* ImageManager::GetImage(const char* name) {
	if (name == nullptr) { return nullptr; }

	//Engine::getInstance().Sys_Printf("Find image %s \n", name);

	//find image by name
	m_it = m_images.find(name);

	//if not found, create new texture
	if (m_it == m_images.end()) {
		Texture2D* texture = TYW_NEW Texture2D(name, TEXTURE_LOCATION);

		//check if texture was loaded
		if (!texture->IsLoaded()) 
		{
		//	Engine::getInstance().Sys_Printf("ERROR: Could not find texture %s\n", name);
			SAFE_DELETE(texture);
			return nullptr;
		}
		else 
		{
			InsertImage(texture);
			return texture;
		}
	}
	else 
	{
		//Engine::getInstance().Sys_Printf("Material %s is already in the system \n", name);
		return m_it->second;
	}
}


void ImageManager::InsertImage(Texture2D* image) {
	if (image == nullptr) { return; }
	m_images.insert(map::value_type(image->getName(), image));
}

void ImageManager::PurgeAllImages() 
{
	for (m_it = m_images.begin(); m_it != m_images.end(); ++m_it) 
	{
		m_it->second->Clear();
		SAFE_DELETE(m_it->second);
	}
}