#ifndef _I_GAME_VIEW_H_
#define _I_GAME_VIEW_H_


enum GameViewType
{
	GameView_Human,
	GameView_Remote,
	GameView_AI,
	GameView_Recorder,
	GameView_Other
};

struct AppMsg
{
	HWND m_hWnd;
	UINT m_uMsg;
	WPARAM m_wParam;
	LPARAM m_lParam;
};

class IGameView
{
public:
	virtual HRESULT VOnRestore() = 0;
	virtual void VOnRender(double fTime, float fElapsedTime) = 0;
	virtual HRESULT VOnLostDevice() = 0;
	virtual GameViewType VGetType() = 0;
	virtual unsigned int VGetId() const = 0;
	virtual void VOnAttach(unsigned int vid, unsigned int aid) = 0;

	virtual LRESULT CALLBACK VOnMsgProc(AppMsg msg) = 0;
	virtual void VOnUpdate(unsigned long deltaMs) = 0;

	virtual ~IGameView() { };
};

#endif