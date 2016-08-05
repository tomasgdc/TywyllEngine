//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once
#include <Singleton.h>

//forward
struct gl_params;
class IRenderer;

struct frameTiming_t 
{
	uint64_t	startSyncTime;
	uint64_t	finishSyncTime;
	uint64_t	startGameTime;
	uint64_t	finishGameTime;
	uint64_t	finishDrawTime;
	uint64_t	startRenderTime;
	uint64_t	finishRenderTime;
};

class GameThread {

public:
	void			RunGameAndDraw(int numGameFrames_, int startGameFrame);

	// Accessors to the stored frame/thread time information
	void			SetThreadTotalTime(const int inTime) { threadTime = inTime; }
	int				GetThreadTotalTime() const { return threadTime; }

	void			SetThreadGameTime(const int time) { threadGameTime = time; }
	int				GetThreadGameTime() const { return threadGameTime; }

	void			SetThreadRenderTime(const int time) { threadRenderTime = time; }
	int				GetThreadRenderTime() const { return threadRenderTime; }
private:
	void			Run();
	int				gameTime;
	int				drawTime;
	int				threadTime;					// total time : game time + foreground render time
	int				threadGameTime;				// game time only
	int				threadRenderTime;			// render fg time only
	int				numGameFrames;
};

class TYWENGINE_API Engine : public Singleton<Engine>
{

public:
	Engine();
	void				Init(int argc, const char * const * argv, const char *cmdline, int windowWidth, int windowHeight);
	void				Frame();
	void				ShutDown();

	void				InitSysConsole();

	void				Sys_WPrintf(FILE* stream, const wchar_t* szFormat, ...);
	void				Sys_Printf(FILE* stream, const char* szFormat, ...);

	void				Sys_WDebugPrintf(const wchar_t* szFormat, ...);
	void				Sys_DebugPrintf(const char* szFormat, ...);

	void				Sys_WError(FILE* stream, const wchar_t* szFormat, ...);
	void				Sys_Error(FILE* stream, const char* szFormat, ...);

	static bool			ProcessOSEvent(struct sysEvent_t *event);
	static bool			RunOSEvents();

	bool				IsInitialized() const;
	bool				IsRunning() const { return m_bIsRunning; }
public:
	void				Draw();			// called by gameThread

	int					GetGameThreadTotalTime() const { return m_GameThread.GetThreadTotalTime(); }
	int					GetGameThreadGameTime() const { return m_GameThread.GetThreadGameTime(); }
	int					GetGameThreadRenderTime() const { return m_GameThread.GetThreadRenderTime(); }

	frameTiming_t&		GetFrameTiming() { return m_FrameTiming; }
	float				GetDeltaTime() { return m_fDeltaTime; }

private:
	frameTiming_t		m_FrameTiming;
	frameTiming_t		m_MainFrameTiming;
	float				m_fDeltaTime;

	bool				m_bFullyInitialized;
	bool				m_bIsRunning;
	bool				m_bIsSysConsoleRunning;

	int					m_GameFrame;			// Frame number of the local game
	double				m_dGameTimeResidual;	// left over msec from the last game frame


	int					m_iCountNumGameFrames;		// total number of game frames that were run
	int					m_iTime_gameFrame;			// game logic time
	int					m_iTime_maxGameFrame;		// maximum single frame game logic time
	int					m_iTime_gameDraw;			// game present time
	uint64_t			m_iTime_frontend;			// renderer frontend time
	uint64_t			m_iTime_backend;			// renderer backend time
	uint64_t			m_iTime_shadows;			// renderer backend waiting for shadow volumes to be created
	uint64_t			m_iTime_gpu;				// total gpu time, at least for PC

private:
	bool				GL_Init(gl_params parms);
	GameThread			m_GameThread;

	std::shared_ptr<IRenderer> m_pRenderer;
};