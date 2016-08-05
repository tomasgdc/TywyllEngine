#ifndef _GAME_H_
#define _GAME_H_

//forward declaration
class HumanView;
class BaseGameLogic;
class EventManager;
class IRenderer;


#include "BaseGameLogic.h"
#include "GameOptions.h"


class TYWGAME_API Game
{
protected:

	HINSTANCE m_hInstance;					// the module instance
	bool m_bWindowedMode;					// true if the app is windowed, false if fullscreen
	bool m_bIsRunning;						// true if everything is initialized and the game is in the main loop
	bool m_bQuitRequested;					// true if the app should run the exit sequence
	bool m_bQuitting;						// true if the app is running the exit sequence
	int m_iColorDepth;						// current color depth (16 or 32)
	bool m_bIsEditorRunning;				// true if the game editor is running
	
	std::shared_ptr<IRenderer> m_pRenderer;
public:
//	const Point &GetScreenSize() { return m_screenSize; }

protected:
	std::map<std::wstring, std::wstring> m_textResource;
	std::map<std::wstring, UINT> m_hotkeys;

	int m_HasModalDialog;					// determines if a modal dialog is up
	int PumpUntilMessage(UINT msgEnd, WPARAM* pWParam, LPARAM* pLParam);
//	int	EatSpecificMessages(UINT msgType, optional<LPARAM> lParam, optional<WPARAM> wParam);
	void FlashWhileMinimized();

public:

	Game();
	virtual ~Game();


	/*************************************
			GAME CODE SPECIFIC STUFF
	*************************************/
	BaseGameLogic *m_pGame;
	struct GameOptions m_Options;


	BaseGameLogic *VCreateGameAndView();
	bool VLoadGame(void);
	HumanView* GetHumanView();				// Added post press - it was convenient to grab the HumanView attached to the game.

											// File and Resource System
	class ResCache *m_ResCache;
	TCHAR m_saveGameDirectory[MAX_PATH];

	bool IsEditorRunning() { return m_bIsEditorRunning; }


	/*
		Loads game data and register needed events

		@return true if it was loaded succesfully, otherwise false
	*/
	bool InitGame();

	/*
		In here you handle All OS Events which you get from the Engine

		@param const struct  sysEvent_t * pEvent
	*/
	static void  HandleOSEvents(const struct  sysEvent_t * pEvent);


	// Socket manager - could be server or client
	//BaseSocketManager *m_pBaseSocketManager;
	//NetworkEventForwarder* m_pNetworkEventForwarder;
	//bool AttachAsClient();


	// DirectX 11 Specific Stuff
	/*
	static bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
	static HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	static HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	static void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext);
	static void CALLBACK OnD3D11DestroyDevice(void* pUserContext);
	static void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime, float fElapsedTime, void* pUserContext);

	static bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
	static void CALLBACK OnUpdateGame(double fTime, float fElapsedTime, void *pUserContext);
	*/
	

	//Callback functions
	static void OnFrameRender(double fTime, float fElapsedTime);
	static void OnUpdateGame(double fTime, float fElapsedTime);


protected:
//	virtual void VCreateNetworkEventForwarder(void);
//	virtual void VDestroyNetworkEventForwarder(void);

public:

	// Main loop processing
	//void AbortGame() { m_bQuitting = true; }
	//int GetExitCode() { return DXUTGetExitCode(); }
	//bool IsRunning() { return m_bIsRunning; }
	//void SetQuitting(bool quitting) { m_bQuitting = quitting; }

	BaseGameLogic* GetGameLogic(void) const { return m_pGame; }
protected:
	void VRegisterGameEvents(void);
};
#endif