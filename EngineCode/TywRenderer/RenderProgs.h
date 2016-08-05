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
#ifndef _RENDER_PROGS_H_
#define _RENDER_PROGS_H_





//GEOMETRY SHADER -> core since OpenGL 3.2
enum class TYWRENDERER_API shaderEnum 
{
	WRONG_FORMAT,
	FRAGMENT_SHADER,
	VERTEX_SHADER,
	GEOMETRY_SHADER
};

//All listed uniforms are available from OpenGL 3.0 version
//List of OpenGL uniforms -> https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml
enum class TYWRENDERER_API uniformEnum 
{
	WRONG_FORMAT,
	GL_Uniform1f,
	GL_Uniform2f,
	GL_Uniform3,
	GL_Uniform4f,
	GL_Uniform1i,
	GL_Uniform2i,
	GL_Uniform3i,
	GL_Uniform4i,
	GL_Uniform1ui,
	GL_Uniform2ui,
	GL_Uniform3ui,
	GL_Uniform4ui,
	GL_Uniform1fv,
	GL_Uniform2fv,
	GL_Uniform3fv,
	GL_Uniform4fv,
	GL_Uniform1iv,
	GL_Uniform2iv,
	GL_Uniform3iv,
	GL_Uniform4iv,
	GL_Uniform1uiv,
	GL_Uniform2uiv,
	GL_Uniform3uiv,
	GL_Uniform4uiv,
	GL_UniformMatrix2fv,
	GL_UniformMatrix3fv,
	GL_UniformMatrix4fv,
	GL_UniformMatrix2x3fv,
	GL_UniformMatrix3x2fv,
	GL_UniformMatrix2x4fv,
	GL_UniformMatrix4x2fv,
	GL_UniformMatrix3x4fv,
	GL_UniformMatrix4x3fv
};

//Manages GLSL Shader
class TYWRENDERER_API RenderProgManager 
{
public:
	RenderProgManager(){}
	void	Init();
	GLuint	LoadGLSLShader(shaderEnum shader);
	GLuint	LoadGLSLProgram(GLuint fragId, GLuint vertId);
	bool	LoadGLSLUniform(const char* name, uniformEnum unfType);
	void	ConnectGLSLData(const char* index);
	bool	UseProgram(const char* id);
	GLuint	GetProgram(const char* id);
	void	UseProgram(); //UseProgram(0);
	void	DeleteShaders();
	void	SetUniformMatrix4fv(const char* prog, const char* unf, int count, bool transpose, const float* value);
	void	SetUniform4f(const char* prog, const char* unf, float x, float y, float z, float w);
	~RenderProgManager() {}
protected:
	char* LoadResource(const char * rawBuffer); //Returns loded txt file data

	struct glslUniformLocation_t {
		glslUniformLocation_t(): type(uniformEnum::WRONG_FORMAT), uniformIndex(0) {}
		glslUniformLocation_t(GLint uniform, uniformEnum unfType):type(unfType), uniformIndex(uniform) {}
		uniformEnum type;
		GLint	uniformIndex; //uniformLocation
	};
	struct glslProgram_t
	{
		glslProgram_t() :progId(0) {}
		glslProgram_t(GLuint prog):progId(prog){}
		GLuint progId;
		std::unordered_map<std::string, glslUniformLocation_t> uniformLocations;
	};
	std::unordered_map<std::string, glslProgram_t> glslPrograms;
	std::list<glslUniformLocation_t> uniformsLoc;
	std::list<std::string> uniformName;

private:
	std::string buffer; //we use string due to + operator
	GLuint	currentProgram;
	GLuint	currentVertex;
	GLuint	currentFragment;

	GLint	GetUniformLocation(const char* name);
	bool	CheckCompileError(GLuint shaderType);
	bool	ChecLinkingError(GLuint program);
};

extern TYWRENDERER_API RenderProgManager renderProgManager;
#endif
