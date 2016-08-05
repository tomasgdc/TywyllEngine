//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>


//Renderer Includes
#include "GLRenderer.h"
#include "RenderProgs.h"


/*
//=======================================================================
char* LoadResource();
//=======================================================================
*/
char* RenderProgManager::LoadResource(const char * rawBuffer)
{
	if (rawBuffer == nullptr) {
		g_RendGL.LogShv("ERROR: GLSLResourceLoader:LoadResource: passed data = nullptr \n");
		return nullptr;
	}

	char* buffer = nullptr;
	std::ifstream is(rawBuffer, std::ifstream::in);
	if (!is) {
		g_RendGL.LogShv("ERROR: GLSLResourceLoader:LoadResource: could not find file %s \n", rawBuffer);
		return nullptr;
	}
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);
		buffer = TYW_NEW char[length + 1]; //try-catch could be used// memory leak
		buffer[length] = '\0';
		is.read(buffer, length);
		long long rb = is.gcount();
		if (rb < length) {
			memset(buffer + rb, 0, length - rb);
		}
	is.close();
	is.clear();
	return buffer;
}

/*
//=======================================================================
void SetUniformMatrix4fv();
Not the best code -> could be made improvements
Perfomance hit if used in update loop
//=======================================================================
*/
void RenderProgManager::SetUniformMatrix4fv(const char* progIndx, const char* unfIndx, int count, bool transpose, const float* value) {
	if (value == nullptr) {
		g_RendGL.LogShv("ERROR:  RenderProgManager::SetUniformMatrix4fv: passed data = nulltpr \n");
		return;
	}

	std::unordered_map<std::string, glslProgram_t>::iterator it = glslPrograms.find(progIndx);
	if (it == glslPrograms.end()) {
		g_RendGL.LogShv("ERROR:  RenderProgManager::SetUniformMatrix4fv: could not find specified program \n");
		return;
	}

	std::unordered_map<std::string, glslUniformLocation_t>::iterator itUnf = it->second.uniformLocations.find(unfIndx);
	if (itUnf == it->second.uniformLocations.end()) {
		g_RendGL.LogShv("ERROR: RenderProgManager::SetUniformMatrix4fv: could not find specified uniform \n");
		return;
	}
	if (itUnf->second.type != uniformEnum::GL_UniformMatrix4fv) {
		g_RendGL.LogShv("ERROR: RenderProgManager::SetUniformMatrix4fv: wrong uniform format \n");
		return;
	}
	glUniformMatrix4fv(itUnf->second.uniformIndex, count, transpose, value);
}

/*
//=======================================================================
void SetUniform4f();
Not the best code -> could be made improvements
Perfomance hit if used in update loop
//=======================================================================
*/
void RenderProgManager::SetUniform4f(const char* progIndx, const char* unfIndx, float x, float y, float z, float w) {
	std::unordered_map<std::string, glslProgram_t>::iterator it = glslPrograms.find(progIndx);
	if (it == glslPrograms.end()) {
		g_RendGL.LogShv("ERROR:  RenderProgManager::SetUniform4f: could not find specified program \n");
		return;
	}

	std::unordered_map<std::string, glslUniformLocation_t>::iterator itUnf = it->second.uniformLocations.find(unfIndx);
	if (itUnf == it->second.uniformLocations.end()) {
		g_RendGL.LogShv("ERROR: RenderProgManager::SetUniform4f: could not find specified uniform \n");
		return;
	}
	if (itUnf->second.type != uniformEnum::GL_Uniform4f) {
		g_RendGL.LogShv("ERROR: RenderProgManager::SetUniform4f: wrong uniform format \n");
		return;
	}
	glUniform4f(itUnf->second.uniformIndex, x, y, z, w);
}
/*
//=======================================================================
void ConnectGLSLData();
//=======================================================================
*/
void RenderProgManager::ConnectGLSLData(const char* index) {

	if (currentProgram == 0 && currentFragment == 0 && currentVertex == 0) {
		g_RendGL.LogShv("ERROR: RenderProgManager::ConenctGLSLData: progId && vertId && fragId == 0 \n");
		return;
	}
	glslProgram_t program(currentProgram);
	std::list<glslUniformLocation_t>::iterator it;
	std::list<std::string>::iterator itN = uniformName.begin();
	for (it = uniformsLoc.begin(); it != uniformsLoc.end(); ++it) {
		program.uniformLocations.insert
			(std::map<std::string, glslUniformLocation_t>::value_type(*itN, *it));
		++itN;
	}
	uniformsLoc.clear(); //make data ready for new uniforms
	glslPrograms.insert(std::map<std::string, glslProgram_t>::value_type(index, program));
}

/*
//=======================================================================
bool LoadGLSLUniform();
//=======================================================================
*/
bool RenderProgManager::LoadGLSLUniform(const char* name, uniformEnum unfType) {
	GLint loc = GetUniformLocation(name);
	if (loc == -1) {
		return false;
	}
	glslUniformLocation_t tempUniform(loc, unfType);
	uniformsLoc.push_back(tempUniform);
	uniformName.push_back(name);
}


/*
//=======================================================================
GLint GetUniformLocation();
//=======================================================================
*/
GLint RenderProgManager::GetUniformLocation(const char* name) {
	if (name == nullptr) {
		g_RendGL.LogShv("ERROR: RenderProgManager::GetUnifromLocation: name == nullptr \n");
		return -1;
	}
	if (currentProgram == 0) {
		g_RendGL.LogShv("ERROR: RenderProgManager::GetUniformLocation: var currentProgram == 0 \n");
		return -1;
	}

	GLint loc = glGetUniformLocation(currentProgram, name);
	if (loc == -1) {
		g_RendGL.LogShv("ERROR: RenderProgManager::GetUniformLoaction: could not find-> %s \n", name);
		return -1;
	}
	return loc;
}

/*
//=======================================================================
bool UseProgram();
//=======================================================================
*/
bool RenderProgManager::UseProgram(const char* id) {
	std::unordered_map<std::string, glslProgram_t>::const_iterator got = glslPrograms.find(id);
	if (got == glslPrograms.end()) {
		g_RendGL.LogShv("ERROR: RenderProgManager::UseProgram: could not find specified program \n");
		return false;
	}
	if (got->second.progId == 0) {
		g_RendGL.LogShv("ERROR: RenderProgManager::UseProgram: programId == 0 \n");
		return false;
	}
	glUseProgram(got->second.progId);
	return true;
}

/*
//=======================================================================
GLuint GetProgram
//=======================================================================
*/
GLuint RenderProgManager::GetProgram(const char* id) {
	std::unordered_map<std::string, glslProgram_t>::const_iterator got = glslPrograms.find(id);
	if (got == glslPrograms.end()) {
		g_RendGL.LogShv("ERROR: RenderProgManager::UseProgram: could not find specified program \n");
		return 0;
	}
	if (got->second.progId == 0) {
		g_RendGL.LogShv("ERROR: RenderProgManager::UseProgram: programId == 0 \n");
		return 0;
	}
	return got->second.progId;
}
/*
//=======================================================================
void UseProgram();
//=======================================================================
*/
void RenderProgManager::UseProgram() {
	glUseProgram(0);
}

/*
//=======================================================================
void DeleteShaders();
//=======================================================================
*/
void RenderProgManager::DeleteShaders() {
	std::unordered_map<std::string, glslProgram_t>::iterator progIt;
	for (progIt = glslPrograms.begin(); progIt != glslPrograms.end(); ++progIt) {
		if (progIt->second.progId != 0)
		{
			glDeleteShader(progIt->second.progId);
		}
		progIt->second.uniformLocations.clear();
	}
	uniformsLoc.clear();
	glslPrograms.clear();
}

/*
//=======================================================================
GLuint LoadGLSLProgram();
//=======================================================================
*/
GLuint RenderProgManager::LoadGLSLProgram(GLuint fragId, GLuint vertId) {
	const GLuint program = glCreateProgram();
	if (program == 0) {
		g_RendGL.LogShv("ERROR: RenderProgManager::LoadGLSLProgram: could not create program \n");
		return 0;
	}
	if (fragId != 0 && vertId != 0) {
		glAttachShader(program, fragId);
		glAttachShader(program, vertId);
	}
	else {
		g_RendGL.LogShv("ERROR: RenderProgManager::LoadGLSLProgram: currentVertex && currentFragment == 0 \n");
		return 0;
	}

	glLinkProgram(program);
	if (!ChecLinkingError(program))
	{
		g_RendGL.LogShv("RenderProgManager::LoadGLSLProgram: CheckLinkingError() returned false \n");
		return 0;
	}
	return program;
}

/*
//=======================================================================
GLuint LoadGLSLShader();
//=======================================================================
*/
GLuint RenderProgManager::LoadGLSLShader(shaderEnum shader) {

	GLuint shaderType = 0; //Could go wrong
	switch (shader)
	{
	case shaderEnum::FRAGMENT_SHADER:	shaderType = glCreateShader(GL_FRAGMENT_SHADER);   break;
	case shaderEnum::VERTEX_SHADER:		shaderType = glCreateShader(GL_VERTEX_SHADER);   break;
	}

	//Loaded glsl text data -> check if not empty
	if (buffer.empty()) {
		g_RendGL.LogShv("ERROR: RenderProgManager::LoadGLSLShader: No data in buffer \n");
		return 0;
	}

	//Copy data to tempBuffer that original data would not be changed
	std::string tempBuffer = buffer;
	switch (shader)
	{
	case shaderEnum::FRAGMENT_SHADER:
		tempBuffer = "#define FRAGMENT_SHADER\n" + buffer;
		break;
	case shaderEnum::VERTEX_SHADER:
		tempBuffer = "#define VERTEX_SHADER\n" + buffer;
		break;
	default:
		break;
	}
	//version number has always to come up first in GLSL shader -> otherwise error from compiler
	tempBuffer = "#version 430 core\n" + tempBuffer;
	const char* c_str = tempBuffer.c_str();

	glShaderSource(shaderType, 1, &c_str, nullptr); //get the shader source
	glCompileShader(shaderType); //compile shader
	if (!CheckCompileError(shaderType)) {
		g_RendGL.LogShv("ERROR: RenderProgManager::LoadGLSLShader: CheckCompileError() returned false \n");
		return 0;
	}
	//c_str = null-> should I delete shader if compiler throws error?
	return shaderType;
}

/*
//=======================================================================
RenderProgManager::CheckCompileError
//=======================================================================
*/
bool RenderProgManager::CheckCompileError(GLuint shaderType) {
	GLint success = 0;
	glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint logSize = 0;
		glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &logSize);
		GLchar* error = TYW_NEW GLchar[logSize];
		glGetShaderInfoLog(shaderType, logSize, NULL, error);

		g_RendGL.LogShv("%s \r\n", error);
		SAFE_DELETE_ARRAY(error);
		return false;
	}
	return true;
}

/*
//=======================================================================
RenderProgManager::ChecLinkingError
//=======================================================================
*/
bool RenderProgManager::ChecLinkingError(GLuint program) {
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* error = TYW_NEW GLchar[maxLength];
		glGetProgramInfoLog(program, maxLength, &maxLength, error);

		g_RendGL.LogShv("%s \r\n", error);
		SAFE_DELETE_ARRAY(error);
		return false;
	}
	return true;
}