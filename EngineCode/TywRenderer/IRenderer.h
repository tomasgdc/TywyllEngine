#pragma once

#define MAXIMUM_LIGHTS_SUPPORTED 8


#include "Lights.h"
#include "OpenGL\BufferObject.h"

class TYWRENDERER_API IRenderState
{
public:
	virtual std::string VToString() = 0;
};



class TYWRENDERER_API IRenderer
{
public:
	virtual ~IRenderer(){}

	virtual bool VInitRenderer(uint32_t height, uint32_t widht, bool isFullscreen, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM)) = 0;
	virtual void VSetBackgroundColor(BYTE bgA, BYTE bgR, BYTE bgG, BYTE bgB) = 0;
	virtual HRESULT VOnRestore() = 0;
	virtual void VShutdown() = 0;
	virtual bool VPreRender() = 0;
	virtual bool VPostRender() = 0;
	virtual void VCalcLighting(Lights *lights, int maximumLights) = 0;
	virtual void VSetWorldTransform(const glx::mat4<float> *m) = 0;
	virtual void VSetViewTransform(const glx::mat4<float> *m) = 0;
	virtual void VSetProjectionTransform(const glx::mat4<float> *m) = 0;
	virtual std::shared_ptr<IRenderState> VPrepareAlphaPass() = 0;
	virtual std::shared_ptr<IRenderState> VPrepareSkyBoxPass() = 0;
	virtual void VDrawLine(const glx::vec3<float>& from, const glx::vec3<float>& to, const glx::vec4<float>& color) = 0;
	
	//virtual void SwapCommandsFinnishRendering(uint64_t* gpuMicroSec) = 0;
	
	virtual void StartFrame() = 0;
	virtual void EndFrame(uint64_t* gpuMicroSec) = 0;
};

