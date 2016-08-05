//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once



#include "IRendererInitializer.h"


#define	WINDOW_STYLE	(WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE | WS_THICKFRAME)

class WindowsGLRendererInitializer final: public IRendererInitializer
{
	friend class GLRenderer;

public:
	WindowsGLRendererInitializer();
	~WindowsGLRendererInitializer();

	bool CreateRendererScreen(uint32_t height, uint32_t widht, bool isFullscreen, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM));
	void DestroyRendererScreen();


	HWND GetWind32Handle() { return m_hWnd; }


	/*
	if interval = 0 then vsync is disabled
	if interval = 1 then vsync is enabled
	if intervak = -1 then adaptive vsync is enabled

	Adaptive vsync enables v-blank synchronisation when the frame rate is higher than the sync rate,
	but disables synchronisation when the frame rate drops below the sync rate.
	Disabling the synchronisation on low frame rates prevents the common problem where the frame rate
	syncs to a integer fraction of the screen's refresh rate in a complex scene.
	*/
	void RendererSwapBuffers();

protected:

	int WGLChoosePixelFormat(const HDC hdc, const uint32_t multisamples, const bool stereo3D);

	//Used only to get wglExtension
	static LONG WINAPI CreateFakeWndProc(HWND    hWnd, UINT    uMsg, WPARAM  wParam, LPARAM  lParam);

	//Checks if wgl extensions are supported on this hardware
	bool CheckWGLExtensions(HDC hDC);


	void GetWGLExtensionsWithFakeWindow();


	HGLRC CreateOpenGLContextOnDC(const HDC hdc, const bool debugContext);


	void CreateWindowClasses(LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM));

	/*
	Set the pixelformat for the window before it isshown, and create the rendering context
	@param gl_params: user params that are in GLRenderer
	*/
	bool InitDriver();

	/*
	Responsible for creating the Win32 window.
	If fullscreen, it won't have a border
	*/
	bool WGLCreateWindow();


protected:
	glconfig_st					m_glConfigs;
	gl_params					m_glParams;

	HWND						m_hWnd;			//Window handle
	HINSTANCE					m_hInstance;
	HINSTANCE					m_hinstOpenGL;	// HINSTANCE for the OpenGL library
	PIXELFORMATDESCRIPTOR		m_pfd;


	HDC							m_hDC;						// handle to device context
	HGLRC						m_hGLRC;						// handle to GL rendering context

	uint32_t					m_iPixelFormat;
	uint32_t					m_iDesktopBitsPixel;
	uint32_t					m_iDesktopWidth;
	uint32_t					m_iDesktopHeight;

	bool						m_bWindowClassRegistered;
};

