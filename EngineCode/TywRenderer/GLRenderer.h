//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once


//forward declared
class GLLineDrawer;
struct srfTriangles_t;
struct glconfig_st;
struct gl_params;

#include "IRenderer.h"


struct glconfig_st
{
	const char *		renderer_string;
	const char *		vendor_string;
	const char *		version_string;
	const char *		extensions_string;
	const char *		wgl_extensions_string;
	const char *		shading_language_string;

	float				fGLVersion;
	float				fMaxTextureAnisotropy;

	uint32_t			iNumbOfSuppExt;			//number of supported extensions
	uint32_t			iMaxTextureSize;			// queried from GL
	uint32_t			iMaxTextureCoords;
	uint32_t			iMaxTextureImageUnits;
	uint32_t			iUniformBufferOffsetAlignment;
	
	uint32_t			iColorBits;
	uint32_t			iDepthBits;
	uint32_t			iStencilBits;

	uint32_t			iNativeScreenWidth; // this is the native screen width resolution of the renderer
	uint32_t			iNativeScreenHeight; // this is the native screen height resolution of the renderer
	uint32_t			iDisplayFrequency;
	uint32_t			iMultiSamples;
	uint32_t			iNumbMonitor;	// monitor number

	bool				bIsStereoPixelFormat;
	bool				bStereoPixelFormatAvailable;
	bool				bSyncAvailable;
	bool				bSwapControlTearAvailable;		//adaptive vsync
	bool				bTimerQueryAvailable;
	bool				bIsFullScreen;
};

#pragma pack(push, 1)
struct gl_params
{
	uint32_t		iXCoord; //screen position in x
	uint32_t		iYCoord; //screen position in y
	uint32_t		iWidth;
	uint32_t		iHeight;
	uint32_t		iDisplayHz;

	// -1 = borderless window for spanning multiple display
	// 0 = windowed, otherwise 1 based monitor number to go full screen on
	uint16_t		iFullScreen;		
	uint16_t		iMultiSamples;
	uint16_t		iSwapInterval;	// 0 - no vsync | 1 - vsync on | 2 - adaptive vsync
	bool			bStereo;
};
#pragma pack(pop)


#include "WindowsGLRendererInitializer.h"

class TYWRENDERER_API GLRenderer final: public IRenderer
{
public:
	GLRenderer();
	~GLRenderer();

	void VShutdown();

	bool VInitRenderer(uint32_t height, uint32_t widht, bool isFullscreen, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM));

	void VSetBackgroundColor(BYTE bgA, BYTE bgR, BYTE bgG, BYTE bgB)
	{
		m_backgroundColor[0] = float(bgA) / 255.0f;
		m_backgroundColor[1] = float(bgR) / 255.0f;
		m_backgroundColor[2] = float(bgG) / 255.0f;
		m_backgroundColor[3] = float(bgB) / 255.0f;
	}

	bool VPreRender();
	bool VPostRender();
	HRESULT VOnRestore();
	void VCalcLighting(Lights *lights, int maximumLights);

	// These three functions are done for each shader, not as a part of beginning the render - so they do nothing in D3D11.
	void VSetWorldTransform(const glx::mat4<float> *m);
	void VSetViewTransform(const glx::mat4<float> *m);
	void VSetProjectionTransform(const glx::mat4<float> *m);

	void VDrawLine(const glx::vec3<float>& from, const glx::vec3<float>& to, const glx::vec4<float>& color);

	std::shared_ptr<IRenderState> VPrepareAlphaPass();
	std::shared_ptr<IRenderState> VPrepareSkyBoxPass();


	//Creates files for logging
	void VSetLogPath();

	//Clears screens and swaps buffers
	//void SwapCommandsFinnishRendering(uint64_t* gpuMicroSec);

	void StartFrame();
	void EndFrame(uint64_t* gpuMicroSec);
public:
	//Log Renderer
	void   Logv(const char* format, ...);

	//Log Rendering Streaming
	void   LogStrv(char* format, ...);

	//Log Renderer Shaders
	void   LogShv(char* format, ...);

	//Prints directly log info to screen
	void   Log(char* str,...);


protected:
	//Calculates swap command and calculates how much time gpu took to process requests
	void SwapCommandBuffers_FinnishRendering(uint64_t* gpuMicroSec);

	void GLCheckErrors();

	void inline GLClearScreen();

	void inline GLClearDepthBuffer();

	void inline GLEnable();


protected:
	//Log Renderer
	FILE*                     m_LogFile;

	//Log Rendering Streaming
	FILE*                     m_LogFileStr;

	//Log Renderer Shaders
	FILE*                     m_LogFileSh;

protected:
	bool								m_bIsOpenglRunning;
	bool								m_bLogRenderer;
	uint32_t							m_iTimerQueryId;
	float								m_backgroundColor[4];

	glconfig_st							m_glConfigs;
	gl_params							m_glParams;

	GLLineDrawer					   *m_pLineDrawer;
	IRendererInitializer			   *m_pWRenderer;
};

extern  GLRenderer g_RendGL;
extern TYWRENDERER_API IRenderer * g_pRendGL;



struct TYWRENDERER_API ConstantBuffer_Lighting
{
	glx::vec4<float> m_vLightDiffuse[MAXIMUM_LIGHTS_SUPPORTED];
	glx::vec4<float> m_vLightDir[MAXIMUM_LIGHTS_SUPPORTED];
	glx::vec4<float> m_vLightAmbient;
	UINT m_nNumLights;
	glx::vec3<float> m_vUnused;
};


class TYWRENDERER_API GLLineDrawer
{
public:
	GLLineDrawer() :m_pVertexBuffer(nullptr) {}
	~GLLineDrawer() 
	{
		m_pVertexBuffer->FreeBufferObject();
		SAFE_DELETE(m_pVertexBuffer);
	}

	void DrawLine(const glx::vec3<float>& from, const glx::vec3<float>& to, const glx::vec4<float>& color) {}
	HRESULT OnRestore() { return 0; }

protected:
	glx::vec3<float>			m_Verts[2];
	VertexBuffer*               m_pVertexBuffer;
};


/*
============================================================
TR_TRISURF
============================================================
*/

srfTriangles_t *	R_AllocStaticTriSurf();
void				R_AllocStaticTriSurfVerts(srfTriangles_t *tri, int numVerts);
void				R_AllocStaticTriSurfIndexes(srfTriangles_t *tri, int numIndexes);

void				R_FreeStaticTriSurfSilIndexes(srfTriangles_t *tri);
void				R_FreeStaticTriSurf(srfTriangles_t *tri);
void				R_FreeStaticTriSurfVerts(srfTriangles_t *tri);

void				R_CreateStaticBuffersForTri(srfTriangles_t & tri);
//=============================================




/*
TESTING
*/
TYWRENDERER_API bool		ImGui_ImplGlfwGL3_Init(IRendererInitializer *m_pWRenderer, bool install_callbacks);
TYWRENDERER_API void        ImGui_ImplGlfwGL3_Shutdown();
TYWRENDERER_API void		ImGui_ImplGlfwGL3_NewFrame(double dCurrentTime,  struct Win32vars & winVars);

// Use if you want to reset your rendering device without losing ImGui state.
TYWRENDERER_API void        ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
TYWRENDERER_API bool        ImGui_ImplGlfwGL3_CreateDeviceObjects();
TYWRENDERER_API bool		ImGui_ImplGlfwGL3_CreateFontsTexture();
TYWRENDERER_API bool		ImguiRender();
//
