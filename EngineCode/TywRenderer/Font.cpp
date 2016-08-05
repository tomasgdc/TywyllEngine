//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\VertData.h>
#include <TywLib\geometry\JointTransform.h>

//Renderer Includes
#include "OpenGL\BufferObject.h"
#include "OpenGL\Texture2D.h"


#include "ThirdParty\FreeType\FreetypeLoad.h"
#include "Font.h"


/*
=======================================
Font::Font
=======================================
*/

Font::Font():vao(0), vbo(0), data(nullptr), buffer(nullptr) {
	try {
		data = TYW_NEW GlyphData();
		buffer = TYW_NEW VertexBuffer();
	}
	catch (...) {
		//Engine::getInstance().Sys_Printf("ERROR: Font::Font(): could not allocate data for VBuffer and GlyphData \n");
	}
}

/*
=======================================
Font::CreateFont
=======================================
*/
void Font::CreateFontGL(const char* strTypeface, int point_size, int dpi) {
	if (!data->LoadGlyph(strTypeface, point_size, dpi)) {
		//Engine::getInstance().Sys_Printf("%s \n", data->getLog().c_str());
		return;
	}
	buffer->AllocateBufferObject(nullptr, sizeof(drawVert)*6, enumBuffer::DYNAMIC_DRAW);
}

/*
=======================================
Font::InitializeChars
=======================================
*/
void Font::InitializeChars(char* source) {
	if (!data->InitiliazeChars(source)) {
		//Engine::getInstance().Sys_Error("%s \n", data->getLog().c_str());
		//Engine::getInstance().Sys_DebugPrintf("ERROR: Font::InitializeChars: returned false \n");
	}
	
	size_t size = strlen(source);
	for (int i = 0; i < size; i++) {
		Data temp = data->getChar(source[i]);
		if (temp.bitmap_buffer != nullptr && temp.c == source[i]) {
			Texture2D texture;
			
			texture.GenerateTexture(temp.bitmap_buffer, temp.bitmap_width, temp.bitmap_rows, texFormat::GLX_RED);
			glyphs.insert(std::unordered_map<char, GLuint>::value_type(source[i], texture.getId()));
		}
		else {
			//Engine::getInstance().Sys_Error("ERROR: Could not find char %c\n", source[i]);
		}
	}
	//I do not need anymore glyph buffer data, so I delete it
	data->ReleaseBuffer();
}


/*
=======================================
Font::DisplayText()
=======================================
*/
void Font::DisplayText(float x, float y, float ws, float hs, const char* text)
{
	
	buffer->EnableVAO();
	buffer->EnableVBO();
	size_t size = strlen(text);
	
	for (int i = 0; i < size; i++) {

		if (text[i] == ' ') {
			x += 32*ws;
			continue;
		}

		Data currentGlyph = data->getChar(text[i]);
#ifndef TYW_DEBUG
		if (currentGlyph.c != text[i]) {
			//Engine::getInstance().Sys_Error("ERROR: Could not find char %c \n", text[i]);
			return;
		}
#endif

		float vx = x + currentGlyph.bitmap_left * ws;
		float vy = y + currentGlyph.bitmap_top * hs;
		float w = currentGlyph.bitmap_width * ws;
		float h = currentGlyph.bitmap_rows * hs;
		
		drawVert data[6] =
		{
			{ glx::vec3<float>(vx,vy,    1),	glx::vec3<float>(0,0,0), glx::vec2<float>(0,0) },
			{ glx::vec3<float>(vx,vy-h,  1),    glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
			{ glx::vec3<float>(vx+w,vy,  1),    glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },

			{ glx::vec3<float>(vx+w,vy,  1),    glx::vec3<float>(0,0,0), glx::vec2<float>(1,0) },
			{ glx::vec3<float>(vx,vy-h,  1),    glx::vec3<float>(0,0,0), glx::vec2<float>(0,1) },
			{ glx::vec3<float>(vx+w,vy-h,1),    glx::vec3<float>(0,0,0), glx::vec2<float>(1,1) }
		};
		glBindTexture(GL_TEXTURE_2D, glyphs.at(text[i])); //Bind texture
		buffer->Update(data, sizeof(drawVert)*6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// increment position /
		x += (currentGlyph.advance.x >> 6) * ws;
		y += (currentGlyph.advance.y >> 6) * hs;
	}
	buffer->DisableVAO();
}

/*
=======================================
Font::Release()
=======================================
*/
bool Font::Release() {
	if (!data->Release()) {
		//Engine::getInstance().Sys_DebugPrintf("ERROR: Font::Release: Glyph data could not be released\n");
		return false;
	}

	glyphs.clear();
	SAFE_DELETE(data);
	SAFE_DELETE(buffer);
	return true;
}

/*
=============================
~Font
=============================
*/
Font::~Font() {
	//Release();
}
