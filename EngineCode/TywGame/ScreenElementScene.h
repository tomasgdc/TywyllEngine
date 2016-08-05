#ifndef _SCREEN_ELEMENT_SCENE_H_
#define _SCREEN_ELEMENT_SCENEN_H_

//forward declaration
class IRenderer;

#include "IScreenElement.h"
//#include <TywRenderer\SceneManager.h>

class ScreenElementScene : public IScreenElement
{
public:
	ScreenElementScene(std::shared_ptr<IRenderer> renderer){ }
	virtual ~ScreenElementScene(void)
	{
		//GCC_WARNING("~ScreenElementScene()");
	}

	/*
	// IScreenElement Implementation
	virtual void VOnUpdate(int deltaMS) { OnUpdate(deltaMS); };
	virtual HRESULT VOnRestore()
	{
		OnRestore(); return S_OK;
	}
	virtual HRESULT VOnRender(double fTime, float fElapsedTime)
	{
		OnRender(); return S_OK;
	}
	virtual HRESULT VOnLostDevice()
	{
		OnLostDevice(); return S_OK;
	}
	virtual int VGetZOrder() const { return 0; }
	virtual void VSetZOrder(int const zOrder) { }

	// Don't handle any messages
	virtual LRESULT CALLBACK VOnMsgProc(AppMsg msg) { return 0; }

	virtual bool VIsVisible() const { return true; }
	virtual void VSetVisible(bool visible) { }
	virtual bool VAddChild(ActorId id, std::shared_ptr<ISceneNode> kid) { return Scene::AddChild(id, kid); }
	*/
};



#endif