#ifndef _MAIN_VIEW_H_
#define _MAIN_VIEW_H_

//forward declaration
class SceneNode;
class IRenderer;

#include "HumanView.h"


/*
	This is main character view
*/
class MainView : public HumanView
{
protected:
	bool  m_bShowUI;					// If true, it renders the UI control text
	std::wstring m_gameplayText;

	//std::shared_ptr<TeapotController> m_pTeapotController;
	//std::shared_ptr<MovementController> m_pFreeCameraController;
	std::shared_ptr<SceneNode> m_pTeapot;
	//std::shared_ptr<StandardHUD> m_StandardHUD;

public:
	MainView(IRenderer* pRenderer);
	virtual ~MainView();

	virtual LRESULT CALLBACK VOnMsgProc(AppMsg msg);
	virtual void VRenderText();
	virtual void VOnUpdate(unsigned long deltaMs);
	virtual void VOnAttach(unsigned int vid, unsigned int aid);

	virtual void VSetControlledActor(unsigned int actorId);
	virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData) override;

	// event delegates
	void GameplayUiUpdateDelegate(IEventDataPtr pEventData);
	void SetControlledActorDelegate(IEventDataPtr pEventData);

private:
	void RegisterAllDelegates(void);
	void RemoveAllDelegates(void);
};

#endif