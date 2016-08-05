//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Renderer Includes
#include "GLRenderer.h"
#include "RenderProgs.h"

GLRenderer g_RendGL;
IRenderer* g_pRendGL = &g_RendGL;


GLRenderer::GLRenderer(): m_pWRenderer(nullptr), m_pLineDrawer(nullptr), m_bIsOpenglRunning(false)
{
#ifdef _DEBUG
	m_bLogRenderer = true;
#endif
}

GLRenderer::~GLRenderer()
{
	SAFE_DELETE(m_pLineDrawer);
	SAFE_DELETE(m_pWRenderer);
}

void GLRenderer::VShutdown()
{
	ImGui_ImplGlfwGL3_Shutdown();
	renderProgManager.DeleteShaders();
	m_pWRenderer->DestroyRendererScreen();
}

bool GLRenderer::VPreRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	return true;
}


bool GLRenderer::VPostRender()
{
	return true;
}

bool GLRenderer::VInitRenderer(uint32_t height, uint32_t width, bool isFullscreen, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM))
{

	//Initialize Logging
	VSetLogPath();

	
#if defined (WIN32) || defined(_WIN32)
	m_pWRenderer = TYW_NEW WindowsGLRendererInitializer;
#endif

	//Create Screen
	if (!m_pWRenderer->CreateRendererScreen(height, width, isFullscreen, MainWindowProc))
	{
		Logv("Error: Could not create window screen for renderer at %s line %d \n", __FILE__, __LINE__);
		return false;
	}
	
	//Initialize Shaders
	renderProgManager.Init();

	m_bIsOpenglRunning = true;


	//TESTING. Initialize ImGui
	ImGui_ImplGlfwGL3_Init(m_pWRenderer, true);


	return true;
}

HRESULT GLRenderer::VOnRestore()
{
	return IDH_OK;
}


void GLRenderer::VCalcLighting(Lights *lights, int maximumLights) 
{

}


void GLRenderer::VSetWorldTransform(const glx::mat4<float> *m)
{

}

void GLRenderer::VSetViewTransform(const glx::mat4<float> *m)
{

}

void GLRenderer::VSetProjectionTransform(const glx::mat4<float> *m)
{

}

void GLRenderer::VDrawLine(const glx::vec3<float>& from, const glx::vec3<float>& to, const glx::vec4<float>& color)
{

}

std::shared_ptr<IRenderState> GLRenderer::VPrepareAlphaPass()
{
	return nullptr;
}


std::shared_ptr<IRenderState> GLRenderer::VPrepareSkyBoxPass()
{
	return nullptr;
}


void GLRenderer::StartFrame()
{
	//Clear the screen
	GLClearScreen();
	GLClearDepthBuffer();

	//Enable GL Stuff
	GLEnable();

}


void GLRenderer::EndFrame(uint64_t* gpuMicroSec)
{
	if (gpuMicroSec != nullptr) {
		*gpuMicroSec = 0;
	}

	if (!m_bIsOpenglRunning) {
		return;
	}

	//if there is rendering command -> swapBuffer
	m_pWRenderer->RendererSwapBuffers();

	//TODO: -> m_glConfigs.timerQueryAvailable
	if (true)
	{
		uint64_t drawingTimeNanoseconds = 0;
		if (m_iTimerQueryId != 0)
		{
			glGetQueryObjectui64v(m_iTimerQueryId, GL_QUERY_RESULT, &drawingTimeNanoseconds);
		}
		if (gpuMicroSec != nullptr)
		{
			*gpuMicroSec = drawingTimeNanoseconds / 1000;
		}
	}

	//check for GL errors
	GLCheckErrors();
}


void GLRenderer::SwapCommandBuffers_FinnishRendering(uint64_t* gpuMicroSec)
{
	if (gpuMicroSec != nullptr) {
		*gpuMicroSec = 0;
	}

	if (!m_bIsOpenglRunning) {
		return;
	}

	//if there is rendering command -> swapBuffer
	m_pWRenderer->RendererSwapBuffers();

	//TODO: -> m_glConfigs.timerQueryAvailable
	if (true) 
	{
		uint64_t drawingTimeNanoseconds = 0;
		if (m_iTimerQueryId != 0) 
		{
			glGetQueryObjectui64v(m_iTimerQueryId, GL_QUERY_RESULT, &drawingTimeNanoseconds);
		}
		if (gpuMicroSec != nullptr) 
		{
			*gpuMicroSec = drawingTimeNanoseconds / 1000;
		}
	}

	//check for GL errors
	GLCheckErrors();
}




void GLRenderer::GLClearScreen()
{
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
}

void GLRenderer::GLClearDepthBuffer()
{
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);
}


void GLRenderer::GLEnable()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLRenderer::GLCheckErrors()
{
	int		err;
	char	s[64];
	int		i;

	// check for up to 10 errors pending
	for (i = 0; i < 10; i++) 
	{
		err = glGetError();
		if (err == GL_NO_ERROR) 
		{
			return;
		}
		switch (err) {
		case GL_INVALID_ENUM:
			strcpy(s, "GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			strcpy(s, "GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			strcpy(s, "GL_INVALID_OPERATION");
			break;
		case GL_STACK_OVERFLOW:
			strcpy(s, "GL_STACK_OVERFLOW");
			break;
		case GL_STACK_UNDERFLOW:
			strcpy(s, "GL_STACK_UNDERFLOW");
			break;
		case GL_OUT_OF_MEMORY:
			strcpy(s, "GL_OUT_OF_MEMORY");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			strcpy(s, "GL_INVALID_FRAMEBUFFER_OPERATION");
			break;
		case GL_CONTEXT_LOST:
			strcpy(s, "GL_CONTEXT_LOST");
			break;
		default:
			break;
		}

		if (m_bLogRenderer) 
		{
			Logv("GL Errors: %s \n", s);
		}
	}
}

//TODO: Create File management system
void GLRenderer::VSetLogPath()
{
	m_LogFile = fopen("../LogInfo/GLRendererLog.txt", "w");
	if (!m_LogFile)
	{
		perror("Could not open GLRenderLog.txt");
	}


	m_LogFileStr = fopen("../LogInfo/GLLogStreaming.txt", "w");
	if (!m_LogFileStr)
	{
		perror("Could not open GLLogStreaming.txt");
	}

	m_LogFileSh = fopen("../LogInfo/GLShaderLog.txt", "w");
	if (!m_LogFileStr)
	{
		perror("Could not open GLShaderLog.txt");
	}
}

void  GLRenderer::Logv(const char* format, ...)
{
	va_list argptr;
	if (m_LogFile)
	{
		va_start(argptr, format);
		vfprintf(m_LogFile, format, argptr);
		va_end(argptr);
		fflush(m_LogFile);
	}
}

void   GLRenderer::LogStrv(char* format, ...)
{
	va_list argptr;
	if (m_LogFileStr)
	{
		fprintf(m_LogFileStr, "  ");
		va_start(argptr, format);
		vfprintf(m_LogFileStr, format, argptr);
		va_end(argptr);
		fflush(m_LogFileStr);
	}
}

void   GLRenderer::LogShv(char* format, ...)
{
	va_list argptr;
	if (m_LogFileSh)
	{
		va_start(argptr, format);
		vfprintf(m_LogFileSh, format, argptr);
		va_end(argptr);
		fflush(m_LogFileSh);
	}
}


void   GLRenderer::Log(char* str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	vfprintf(stdout, str, argptr);
	va_end(argptr);
}