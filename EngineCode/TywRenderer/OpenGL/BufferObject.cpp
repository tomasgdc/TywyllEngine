//Copyright Tomas Mikalauskas. All rights reserved.
//Contact ttomas.mikalauskas@gmail.com
#include <stdafx.h>
#include "TywLib\math\GLXMath.h"
#include "TywLib\geometry\VertData.h"


#include "BufferObject.h"
#include "GLRenderer.h"



/*
================================================================================================

VERTEX BUFFER

================================================================================================
*/


VertexBuffer::VertexBuffer():
	m_vbo(0), m_vao(0), m_location(0), m_size(0), offsetInOtherBuffer(0), m_bufferType(enumBuffer::NOT_VALID){
}

void
VertexBuffer::AllocateBufferObject(const void* data, size_t allocSize, enumBuffer bufferType) {
	if (allocSize <= 0) {
		g_RendGL.LogStrv("ERROR: VertexBuffer::AllocateBufferObject: allocSize = %i \n", allocSize);
		return;
	}
	m_size = allocSize;
	m_bufferType = bufferType;

	//Generate VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//Generate VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	switch (m_bufferType) {
	case enumBuffer::DYNAMIC_DRAW:
		glBufferData(GL_ARRAY_BUFFER, allocSize, nullptr, GL_DYNAMIC_DRAW);
		break;
	case enumBuffer::STATIC_DRAW:
		glBufferData(GL_ARRAY_BUFFER, allocSize, nullptr, GL_STATIC_DRAW);
		break;
	case enumBuffer::STREAM_DRAW:
		glBufferData(GL_ARRAY_BUFFER, allocSize, nullptr, GL_STREAM_DRAW);
		break;
	default:
		g_RendGL.LogStrv("Specified bufferType is not implemented \n");
		break;
	}
	if (data != nullptr) {
		Update(data, allocSize);
		
	}
	//Unbind buffer
	DisableVBO();
	DisableVAO();
}

void VertexBuffer::Update(const void* data, size_t allocSize) {
	if (data == nullptr) {
		g_RendGL.LogStrv("ERROR: VertexBuffer::Update: void* data = nullptr \n");
		return;
	}
	
	if (allocSize <= 0) {
		g_RendGL.LogStrv("ERROR: VertexBuffer::Update: allocSize = %i \n", allocSize);
		return;
	}
	if (m_bufferType == enumBuffer::NOT_VALID) { return; }

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(drawVert), (void*)offsetof(drawVert, vertex));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(drawVert), (void*)offsetof(drawVert, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(drawVert), (void*)offsetof(drawVert, tex));
	

	glBufferSubData(GL_ARRAY_BUFFER, GetOffest(), allocSize, data);
}

void VertexBuffer::ClearBufferSubData() const {
	//If you simply wish to clear a buffer object’s data store to a known value
	//Not implemented
	//glClearBufferSubData(GL_ARRAY_BUFFER, )
}

void VertexBuffer::EnableVAO() {
	if (m_vao == 0) {
		g_RendGL.Log("Error: VAO was not created. = 0 \n");
		return;
	}
	glBindVertexArray(m_vao);
		
}

void VertexBuffer::DisableVAO() {
	//glDisableVertexAttribArray(location); //not sure about this one
	glBindVertexArray(0);
}

void VertexBuffer::EnableVBO() {
	if (m_vbo == 0) {
		g_RendGL.Log("Error: VBO was not created. = 0 \n");
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::DisableVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VertexBuffer::FreeBufferObject() {
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);

	if (m_vbo != 0) {
		glDeleteBuffers(1, &m_vbo);
	}
	if (m_vao != 0) {
		glDeleteVertexArrays(1, &m_vao);
	}
}


/*
================================================================================================

INDEX BUFFER

================================================================================================
*/

IndexBuffer::IndexBuffer():
	m_vbo(0), m_size(0), offsetInOtherBuffer(0) {

}

void IndexBuffer::AllocateBufferObject(const void* data, size_t allocSize, GLuint location_) {
	if (allocSize <= 0) {
		//Engine::getInstance().Sys_Printf("ERROR: IndexBuffer::AllocateBufferObject: allocSize = %i \r\n", allocSize);
		return;
	}
	m_size = allocSize;


	//Generate VAO
	//glGenVertexArrays(1, &m_vao);
	//glBindVertexArray(m_vao);

	//Generate VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocSize, nullptr, GL_STATIC_DRAW);

	if (data != nullptr) {
		Update(data, allocSize);

	}
	//Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IndexBuffer::FreeBufferObject() {
	if (m_vbo != 0) {
		glDeleteBuffers(1, &m_vbo);
	}
//	if (m_vao != 0) {
//		glDeleteVertexArrays(1, &m_vao);
//	}

}

void IndexBuffer::Update(const void* data, size_t allocSize) const {
	if (data == nullptr) {
		//Engine::getInstance().Sys_Printf("ERROR: IndexBuffer::Update: void* data = nullptr \r\n");
		return;
	}

	if (allocSize <= 0) {
//		Engine::getInstance().Sys_Printf("ERROR: IndexBuffer::Update: allocSize = %i \r\n", allocSize);
		return;
	}
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, GetOffest(), allocSize, data);
}

void IndexBuffer::ClearBufferSubData() const {
	//If you simply wish to clear a buffer object’s data store to a known value
	//Not implemented
	//glClearBufferSubData(GL_ELEMENT_ARRAY_BUFFER, )
}

void IndexBuffer::EnableVBO() {
	if (m_vbo == 0) {
		return;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
}

void IndexBuffer::DisableVBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
}