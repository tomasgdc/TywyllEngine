//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Renderer Includes
#include "RenderProgs.h"
#include "GLRenderer.h"


RenderProgManager renderProgManager;

/*
========================
Init
========================
*/
void RenderProgManager::Init() 
{
	struct builtinUniforms_t
	{
		uniformEnum type;
		std::string name;
	}builtinsUnf[] = 
	{
		{uniformEnum::GL_UniformMatrix4fv, "mvp" },
		{uniformEnum::GL_Uniform4f,		   "addColor" },
		{uniformEnum::GL_UniformMatrix4fv, "mvp" }
	};

	struct builtinShaders_t {
		std::string index;
		std::string name;
		const int unfsize;
	} builtins[] = 
	{
		{"text.glsl", "../../Bin/Data/shaders/text.glsl", 2},
		{"geo.glsl",  "../../Bin/Data/shaders/geo.glsl", 1}
	};

	int shadersSize = sizeof(builtins) / sizeof(builtins[0]);
	int unf = 0;
	for (int i = 0; i < shadersSize; i++) {
		const char* tempData = LoadResource(builtins[i].name.c_str());
		
		if (tempData == nullptr) {
			continue; //skip
		}
		buffer = std::string(tempData);
		
		currentVertex	=	LoadGLSLShader(shaderEnum::VERTEX_SHADER);
		currentFragment	=	LoadGLSLShader(shaderEnum::FRAGMENT_SHADER);
		currentProgram	=	LoadGLSLProgram(currentFragment, currentVertex);
		for (int j = 0; j < builtins[i].unfsize; j++) {
			LoadGLSLUniform(builtinsUnf[j + unf].name.c_str(), builtinsUnf[j + unf].type);
		}
		unf = builtins[i].unfsize; //next program->get_uniforms
		ConnectGLSLData(builtins[i].index.c_str());
		SAFE_DELETE_ARRAY(tempData); //dont leak data
	}
}