//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>


//Engine Includes
#include <TywEngine\FrameWork\License.h>

//Application Includes
#include <Application\rc\resource.h>


//Renderer Includes
#include "GLRenderer.h"


WindowsGLRendererInitializer::WindowsGLRendererInitializer(): 
	m_bWindowClassRegistered(false),
	m_hWnd(nullptr),
	m_hInstance(nullptr),
	m_hinstOpenGL(nullptr),
	m_hDC(nullptr),
	m_hGLRC(nullptr),
	m_iPixelFormat(0),
	m_iDesktopBitsPixel(0),
	m_iDesktopHeight(0),
	m_iDesktopWidth(0)
{

}


WindowsGLRendererInitializer::~WindowsGLRendererInitializer()
{

}


bool WindowsGLRendererInitializer::CreateRendererScreen(uint32_t height, uint32_t widht, bool isFullscreen, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM))
{
	//Clear data
	memset(&m_glConfigs, 0, sizeof(m_glConfigs));
	memset(&m_glParams, 0, sizeof(m_glParams));


	HDC		hDC;
	m_glParams.iWidth = height;
	m_glParams.iHeight = height;
	m_glParams.iFullScreen = static_cast<uint16_t>(isFullscreen);




	// check our desktop attributes
	hDC = GetDC(GetDesktopWindow());
	m_iDesktopBitsPixel = GetDeviceCaps(hDC, BITSPIXEL);
	m_iDesktopWidth = GetDeviceCaps(hDC, HORZRES);
	m_iDesktopHeight = GetDeviceCaps(hDC, VERTRES);
	m_hDC = hDC;
	ReleaseDC(GetDesktopWindow(), hDC);


	// create our window classes if we haven't already
	CreateWindowClasses(MainWindowProc);

	// getting the wgl extensions involves creating a fake window to get a context,
	// which is pretty disgusting, and seems to mess with the AGP VAR allocation
	GetWGLExtensionsWithFakeWindow();


	if (!WGLCreateWindow()) 
	{
		return false;
	}


	
	m_glConfigs.bIsFullScreen = isFullscreen;
	m_glConfigs.bIsStereoPixelFormat = m_glParams.bStereo;
	m_glConfigs.iNativeScreenWidth = widht;
	m_glConfigs.iNativeScreenHeight = height;
	m_glConfigs.iMultiSamples = m_glParams.iMultiSamples;

	if (!CheckWGLExtensions(m_hDC))
	{
		return false;
	}


	return true;
}


void WindowsGLRendererInitializer::DestroyRendererScreen()
{
	const wchar_t *success[] = { L"failed", L"success" };
	int retVal;

	g_RendGL.Log("Shutting down OpenGL subsystem");



	//set current context to NULL
	if (wglMakeCurrent) 
	{
		retVal = wglMakeCurrent(nullptr, nullptr) != 0;
	}

	//delete HGLRC
	if (m_hGLRC) 
	{
		retVal = wglDeleteContext(m_hGLRC) != 0;
		m_hGLRC = nullptr;
	}

	//release DC
	if (m_hDC) 
	{
		retVal = ReleaseDC(m_hWnd, m_hDC) != 0;
	}

	//destroy window
	if (m_hWnd) 
	{
		ShowWindow(m_hWnd, SW_HIDE);
		CloseWindow(m_hWnd);
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}


int WindowsGLRendererInitializer::WGLChoosePixelFormat(const HDC hdc, const uint32_t multisamples, const bool stereo3D)
{
	FLOAT	fAttributes[] = { 0, 0 };
	int		iAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, ((multisamples > 1) ? 1 : 0),
		WGL_SAMPLES_ARB, multisamples,
		WGL_DOUBLE_BUFFER_ARB, TRUE,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_RED_BITS_ARB, 8,
		WGL_BLUE_BITS_ARB, 8,
		WGL_GREEN_BITS_ARB, 8,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_STEREO_ARB, (stereo3D ? TRUE : FALSE),
		0, 0
	};

	int	pixelFormat;
	UINT numFormats;
	if (!wglChoosePixelFormatARB(hdc, iAttributes, fAttributes, 1, &pixelFormat, &numFormats)) 
	{
		g_RendGL.Logv("Error: failed to choose pixel format. At %s, line %d \n", __FILE__, __LINE__);
		return -1;
	}
	return pixelFormat;
}

LONG WINAPI WindowsGLRendererInitializer::CreateFakeWndProc(HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam) 
{
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
	}

	if (uMsg != WM_CREATE) {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	const static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		8, 0,
		0, 0, 0, 0,
		24, 8,
		0,
		PFD_MAIN_PLANE,
		0,
		0,
		0,
		0,
	};
	int		pixelFormat;
	HDC hDC;
	HGLRC hGLRC;

	hDC = GetDC(hWnd);

	// Set up OpenGL
	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
	hGLRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hGLRC);

	// free things
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hGLRC);
	ReleaseDC(hWnd, hDC);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


bool WindowsGLRendererInitializer::CheckWGLExtensions(HDC hDC) 
{

	//Initialize GLEW
	if (GLEW_OK != glewInit()) 
	{
		g_RendGL.Logv("ERROR: Could not initialize Glew at %s line %d \n", __FILE__, __LINE__);
		return false;
	}

	if (WGL_ARB_extensions_string) 
	{
		m_glConfigs.wgl_extensions_string = (const char *)wglGetExtensionsStringARB(hDC);
	}
	else 
	{
		m_glConfigs.wgl_extensions_string = "";
	}



	// WGL_EXT_swap_control
	if (!wglSwapIntervalEXT) 
	{
		return false;
	}

	m_glConfigs.bSwapControlTearAvailable = glewIsSupported("WGL_EXT_swap_control_tear");
	m_glConfigs.bSyncAvailable = glewIsSupported("GL_ARB_sync");
	m_glConfigs.bTimerQueryAvailable = glewIsSupported("GL_ARB_timer_query");

	if (!glewIsSupported("wglGetPixelFormatAttribivARB")) 
	{
		//g_RendGL.Logv("ERROR: wglGetPixelFormatAttribivARB is not supported on this system \n");
		//return false;
	}
	if (!glewIsSupported("wglChoosePixelFormatARB")) 
	{
		//g_RendGL.Logv("ERROR: wglChoosePixelFormatARB is not supported on this system \n");
		//return false;
	}

	if (!glewIsSupported("wglCreateContextAttribsARB")) 
	{
		//g_RendGL.Logv("ERROR: wglCreateContextAttribsARB is not supported on this system \n");
		//return false;
	}


	m_glConfigs.vendor_string = (const char*)glGetString(GL_VENDOR);
	m_glConfigs.renderer_string = (const char*)glGetString(GL_RENDERER);
	m_glConfigs.version_string = (const char*)glGetString(GL_VERSION);
	m_glConfigs.shading_language_string = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	m_glConfigs.extensions_string = (const char*)glGetString(GL_EXTENSIONS);

	return true;
}

/*
== == == == == == == == ==
GLW_GetWGLExtensionsWithFakeWindow
== == == == == == == == ==
*/
void WindowsGLRendererInitializer::GetWGLExtensionsWithFakeWindow() 
{
	HWND	hWnd;
	MSG		msg;

	// Create a window for the sole purpose of getting
	// a valid context to get the wglextensions
	hWnd = CreateWindow(reinterpret_cast<LPCTSTR>(WIN32_FAKE_WINDOW_CLASS_NAME),
		reinterpret_cast<LPCTSTR> (GAME_NAME),
		WS_OVERLAPPEDWINDOW,
		40, 40,
		800,
		600,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);
	if (!hWnd) 
	{
		g_RendGL.Logv("Error: Couldn't create fake window. Error number: %d. At %s line %d \n", GetLastError(), __FILE__, __LINE__);
	}

	HDC hDC = GetDC(hWnd);
	HGLRC gRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, gRC);
	CheckWGLExtensions(hDC);

	wglDeleteContext(gRC);
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);



	while (GetMessage(&msg, nullptr, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


HGLRC WindowsGLRendererInitializer::CreateOpenGLContextOnDC(const HDC hdc, const bool debugContext) 
{
	unsigned short int useOpenGL43 = 4;
	HGLRC m_hrc = nullptr;

	for (int i = 0; i < 2; i++) 
	{
		const int glMajorVersion = (useOpenGL43 != 3) ? 4 : 3;
		const int glMinorVersion = (useOpenGL43 != 3) ? 3 : 3;
		const int glDebugFlag = debugContext ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;
		const int glProfileMask = (useOpenGL43 != 0) ? WGL_CONTEXT_PROFILE_MASK_ARB : 0;
		const int glProfile = (useOpenGL43 == 3) ? WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : ((useOpenGL43 == 4) ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : 0);
		const int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB,	glMajorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB,	glMinorVersion,
			WGL_CONTEXT_FLAGS_ARB,			glDebugFlag,
			glProfileMask,					glProfile,
			0
		};

		m_hrc = wglCreateContextAttribsARB(hdc, 0, attribs);
		if (m_hrc != nullptr) 
		{
			g_RendGL.Log("Created OpenGL %d.%d context \n", glMajorVersion, glMinorVersion);
			break;
		}

		g_RendGL.Logv("Failed to create OpenGL %d.%d context at %s line %d \n", glMajorVersion, glMinorVersion, __FILE__, __LINE__);
		useOpenGL43 = 3;	// fall back to OpenGL 3.3
	}

	if (m_hrc == nullptr) 
	{
		int	err = GetLastError();
		switch (err) 
		{
		case ERROR_INVALID_VERSION_ARB:
			g_RendGL.Logv("ERROR_INVALID_VERSION_ARB at %s line %d \n", __FILE__, __LINE__);
			break;
		case ERROR_INVALID_PROFILE_ARB:
			g_RendGL.Logv("ERROR_INVALID_PROFILE_ARB at %s line %d \n", __FILE__, __LINE__);
			break;
		default:
			g_RendGL.Logv("Unknown error: while creating OpenGL context. Error message: %s  at %s line %d \n", err, __FILE__, __LINE__);
			break;
		}
	}
	return m_hrc;
}




/*
====================
GLW_CreateWindowClasses
====================
*/
void WindowsGLRendererInitializer::CreateWindowClasses(LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM))
{
	WNDCLASS wc;


	// register the window class if necessary
	if (m_bWindowClassRegistered) 
	{
		return;
	}

	HICON lpIconName(nullptr);
	
	//TODO: Resolve problem -> Throws error
	//lpIconName = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	if(lpIconName == nullptr)
	{
		//TODO: Same here
		//g_RendGL.Logv("%s \n", GetLastError());

		//Use existing one
		//lpIconName = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	}

	
	::ZeroMemory(&wc, 0, sizeof(wc));

	//Register window class
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)MainWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = lpIconName;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (struct HBRUSH__ *)COLOR_GRAYTEXT;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = reinterpret_cast<LPCTSTR> (WIN32_WINDOW_CLASS_NAME);

	if (!RegisterClass(&wc)) 
	{
		g_RendGL.Logv("Error: Could not register window class. Error number: %d. At %s line %s \n", GetLastError(), __FILE__, __LINE__);
		return;
	}


	// now register the fake window class that is only used
	// to get wgl extensions
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WindowsGLRendererInitializer::CreateFakeWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = lpIconName;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (struct HBRUSH__ *)COLOR_GRAYTEXT;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = reinterpret_cast<LPCTSTR> (WIN32_FAKE_WINDOW_CLASS_NAME);

	if (!RegisterClass(&wc))
	{
		g_RendGL.Logv("Error: Could not register fake window class. Error number: %d. At %s line %s \n", GetLastError(), __FILE__, __LINE__);
		return;
	}

	m_bWindowClassRegistered = true;
}


bool WindowsGLRendererInitializer::InitDriver() 
{
	PIXELFORMATDESCRIPTOR src =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,								// version number
		PFD_DRAW_TO_WINDOW |			// support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,					// RGBA type
		32,								// 32-bit color depth
		0, 0, 0, 0, 0, 0,				// color bits ignored
		8,								// 8 bit destination alpha
		0,								// shift bit ignored
		0,								// no accumulation buffer
		0, 0, 0, 0, 					// accum bits ignored
		24,								// 24-bit z-buffer	
		8,								// 8-bit stencil buffer
		0,								// no auxiliary buffer
		PFD_MAIN_PLANE,					// main layer
		0,								// reserved
		0, 0, 0							// layer masks ignored
	};
	// get a DC for our window if we don't already have one allocated
	if (m_hDC == nullptr)
	{

		m_hDC = GetDC(m_hWnd);
		if (m_hDC == nullptr)
		{ 
			g_RendGL.Logv("Error: Could not get DC for OpenGL drivers initialization. Error number: %d. At %s line %d \n", GetLastError(),__FILE__, __LINE__);
			return false;
		}
	}

	//TODO: wglChoosePixelFormat was returning wrong numbers... Fix me
	// the multisample path uses the wgl 
	//if (wglChoosePixelFormatARB) 
	//{
		//m_iPixelFormat = WGLChoosePixelFormat(m_hDC, m_glParams.iMultiSamples, m_glParams.bStereo);
	//}
	//else 
	//{
		// eventually we may need to have more fallbacks, but for
		// now, ask for everything
		if (m_glParams.bStereo)
		{
			src.dwFlags |= PFD_STEREO;
		}

		//
		// choose, set, and describe our desired pixel format.  If we're
		// using a minidriver then we need to bypass the GDI functions,
		// otherwise use the GDI functions.
		//
		if ((m_iPixelFormat = ChoosePixelFormat(m_hDC, &src)) == 0) 
		{
			g_RendGL.Logv("Error: failed to choose pixel format. Error number: %d. At %s line %d \n",  GetLastError(), __FILE__, __LINE__);
			return false;
		}
		g_RendGL.Logv("PIXELFORMAT %d selected \n", m_iPixelFormat);
	//}

	//Clear pixel format data
	memset(&m_pfd, 0, sizeof(m_pfd));

	// get the full info
	DescribePixelFormat(m_hDC, m_iPixelFormat, sizeof(m_pfd), &m_pfd);
	m_glConfigs.iColorBits = m_pfd.cColorBits;
	m_glConfigs.iDepthBits = m_pfd.cDepthBits;
	m_glConfigs.iStencilBits = m_pfd.cStencilBits;

	// XP seems to set this incorrectly
	if (!m_glConfigs.iStencilBits) 
	{
		m_glConfigs.iStencilBits = 8;
	}



	// the same SetPixelFormat is used either way
	if (SetPixelFormat(m_hDC, m_iPixelFormat, &m_pfd) == FALSE) 
	{
		g_RendGL.Logv("Error: failed to set pixel format. Error number: %d. At %s line %d \n", GetLastError(), __FILE__, __LINE__);
		return false;
	}


	// startup the OpenGL subsystem by creating a context and making it current
	m_hGLRC = CreateOpenGLContextOnDC(m_hDC, false);
	if (m_hGLRC == nullptr) 
	{
		g_RendGL.Logv("Error: failed creating hGLRC opengl context. Error number: %d. At %s line %d \n", GetLastError(), __FILE__, __LINE__);
		return false;
	}


	if (!wglMakeCurrent(m_hDC, m_hGLRC)) 
	{
		wglDeleteContext(m_hGLRC);
		m_hGLRC = nullptr;
		g_RendGL.Logv("Error: failed making context current. Error number: %d. At %s line %d \n", GetLastError(), __FILE__, __LINE__);
		return false;
	}
	return true;
}


/*
=======================
GLW_CreateWindow

Responsible for creating the Win32 window.
If fullscreen, it won't have a border
=======================
*/
bool WindowsGLRendererInitializer::WGLCreateWindow() 
{
	int				x, y, w, h;
	if (!GetWindowDimensions(m_glParams, x, y, w, h)) 
	{
		return false;
	}

	int				stylebits;
	int				exstyle;
	if (m_glParams.iFullScreen != 0) 
	{
		exstyle = WS_EX_TOPMOST;
		stylebits = WS_POPUP | WS_VISIBLE | WS_SYSMENU;
	}
	else 
	{
		exstyle = 0;
		stylebits = WINDOW_STYLE | WS_SYSMENU;
	}

	m_hWnd = CreateWindowEx(
		exstyle,
		reinterpret_cast<LPCTSTR>(WIN32_WINDOW_CLASS_NAME),
		reinterpret_cast<LPCTSTR>(GAME_NAME),
		stylebits,
		x, y, w, h,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if (!m_hWnd) 
	{
		g_RendGL.Logv("Error: Couldn't create window. Error number:  %d. At %s line %d \n",GetLastError(), __FILE__, __LINE__);
		return false;
	}

	::SetTimer(m_hWnd, 0, 100, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	

	//makeCurrent NULL frees the DC, so get another
	m_hDC = GetDC(m_hWnd);
	if (!m_hDC) 
	{
		g_RendGL.Logv("Error: failed getting dc. Error number %d. At %s line %d \n", GetLastError(), __FILE__, __LINE__);
		return false;
	}

	// Check to see if we can get a stereo pixel format, even if we aren't going to use it,
	// so the menu option can be 
	if (WGLChoosePixelFormat(m_hDC, m_glParams.iMultiSamples, true) != -1) 
	{
		m_glConfigs.bStereoPixelFormatAvailable = true;
	}
	else 
	{
		m_glConfigs.bStereoPixelFormatAvailable = false;
	}

	if (!InitDriver()) 
	{
		ShowWindow(m_hWnd, SW_HIDE);
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
		return false;
	}

	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	m_glConfigs.bIsFullScreen = static_cast<bool>(m_glParams.iFullScreen);
	return true;
}


void  WindowsGLRendererInitializer::RendererSwapBuffers()
{
	if (!m_glConfigs.bSyncAvailable) {
		glFinish();
	}
	

	int interval = 0;
	if (m_glParams.iSwapInterval == 1) 
	{
		interval = (m_glConfigs.bSwapControlTearAvailable) ? -1 : 1;
	}

	if (wglSwapIntervalEXT) {
		wglSwapIntervalEXT(interval);
	}
	SwapBuffers(m_hDC);
}

