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
#ifndef _VERTEX_BUFF_H
#define _VERTEX_BUFF_H


enum class TYWRENDERER_API enumBuffer
{
	NOT_VALID,
	STREAM_DRAW, 
	STREAM_READ,
	STREAM_COPY, 
	STATIC_DRAW, 
	STATIC_READ,
	STATIC_COPY,
	DYNAMIC_DRAW,
	DYNAMIC_READ,
	DYNAMIC_COPY
};

class TYWRENDERER_API VertexBuffer
{
public:
	VertexBuffer();

	//Allocates data
	void AllocateBufferObject(const void* data, size_t allocSize, enumBuffer bufferType);

	//Deletes allocated data from GPU
	void FreeBufferObject();

	//Updates data on the same buffer
	void Update(const void* data, size_t allocSize);

	//Not implemented
	int  GetOffest() const { return offsetInOtherBuffer; }

	//Not implemented
	void ClearBufferSubData() const;
	
	void EnableVAO();
	void DisableVAO();
	void EnableVBO();
	void DisableVBO();
	~VertexBuffer() {}

private:
	int				offsetInOtherBuffer;	// offset in bytes
	int				m_size; //allocated size in bytes
	GLuint			m_vbo;
	GLuint			m_vao;
	GLuint			m_location;
	enumBuffer		m_bufferType;
};


class TYWRENDERER_API IndexBuffer
{
public:
	IndexBuffer();

	void AllocateBufferObject(const void* data, size_t allocSize, GLuint location_);
	void FreeBufferObject();

	void Update(const void* data, size_t allocSize) const;
	int  GetOffest() const { return offsetInOtherBuffer; }
	void ClearBufferSubData() const;

	void EnableVBO();
	void DisableVBO();

private:
	int				offsetInOtherBuffer;	// offset in bytes
	int				m_size; //allocated size in bytes
	GLuint			m_vbo;
//	GLuint			m_vao;
};

#endif
