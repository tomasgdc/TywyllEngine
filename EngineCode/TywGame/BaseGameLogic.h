#ifndef _BASE_GAME_LOGIC_H_
#define _BASE_GAME_LOGIC_H_
#include "IGameLogic.h"



class PathingGraph;
class ActorFactory;
class LevelManager;
class IGameView;

enum class BaseGameState
{
	BGS_Invalid,
	BGS_Initializing,
	BGS_MainMenu,
	BGS_WaitingForPlayers,
	BGS_LoadingGameEnvironment,
	BGS_WaitingForPlayersToLoadEnvironment,
	BGS_SpawningPlayersActors,
	BGS_Running
};

typedef std::map<unsigned int, StrongActorPtr> ActorMap;
typedef std::string Level;
typedef std::vector<std::shared_ptr<IGameView>> GameViewList;

class LevelManager
{
public:
	const std::vector<Level> &GetLevels() const { return m_Levels; }
	const int GetCurrentLevel() const { return m_CurrentLevel; }
	bool Initialize(std::vector<std::string> &levels);

protected:
	std::vector<Level> m_Levels;
	int m_CurrentLevel;
};



class BaseGameLogic : public IGameLogic
{
	friend class Game;						// This is only to gain access to the view list

protected:
	float									m_Lifetime;									//indicates how long this game has been in session
//	ProcessManager*							m_pProcessManager;							// a game logic entity
	ActorMap								m_actors;
	unsigned int							m_LastActorId;
	BaseGameState							m_State;									// game state: loading, running, etc.
	int										m_ExpectedPlayers;							// how many local human players
	int										m_ExpectedRemotePlayers;					// expected remote human players
	int										m_ExpectedAI;								// how many AI players
	int										m_HumanPlayersAttached;
	int										m_AIPlayersAttached;
	int										m_HumanGamesLoaded;
	GameViewList							m_gameViews;								// views that are attached to our game
	std::shared_ptr<PathingGraph>			m_pPathingGraph;							// the pathing graph
	ActorFactory*							m_pActorFactory;

	bool									m_bProxy;									// set if this is a proxy game logic, not a real one
	int										m_remotePlayerId;							// if we are a remote player - what is out socket number on the server

	bool									m_RenderDiagnostics;						// Are we rendering diagnostics?
	std::shared_ptr<IGamePhysics>			m_pPhysics;

	LevelManager*							 m_pLevelManager;							// Manages loading and chaining levels

public:

	BaseGameLogic();
	virtual ~BaseGameLogic();

	/*
		Initializes game specific stuff

		@return true if game was loaded successfuly, otherwise false
	*/
	bool Init(void);

	/*
		@bool isProxy
	*/
	void SetProxy(bool isProxy)
	{
		m_bProxy = isProxy;
	}

	/*
		Indicates if it is proxy or not

		@return bool
	*/
	const bool IsProxy() const { return m_bProxy; }


	/*
		[mrmike] CanRunLua() is a bit of a hack - but I can't have Lua scripts running on the clients. They should belong to the logic.
		FUTURE WORK - Perhaps the scripts can have a marker or even a special place in the resource file for any scripts that can run on remote clients

		@return bool
	*/
	const bool CanRunLua() const { return !IsProxy() || GetState() != BaseGameState::BGS_Running; }

	/*
		@return actorId
	*/
	unsigned int GetNewActorID(void)
	{
		return ++m_LastActorId;
	}

	/*
		@return std::shared_ptr<PathingGraph>
	*/
	std::shared_ptr<PathingGraph> GetPathingGraph(void) { return m_pPathingGraph; }


	/*
		Adds view

		@param std::shared_ptr<IGameView> pView
		@param unsigned int actorId
	*/
	virtual void VAddView(std::shared_ptr<IGameView> pView, unsigned int actorId = 0);


	/*
		Removes view

		@param std::shared_ptr<IGameView> pView
	*/
	virtual bool VRemoveView(std::shared_ptr<IGameView> pView);


	/*
		@param const std::string &actorResource
		@param tinyxml2::XMLElement *overrides
		@param const glx::mat4<float>* initialTransform
		@param const unsigned int serversActorId
		@return  std::shared_ptr<Actor>
	*/
	virtual StrongActorPtr VCreateActor(const std::string &actorResource, tinyxml2::XMLElement *overrides, const glx::mat4<float>* initialTransform = nullptr, const unsigned int serversActorId = 0);

	/*
		@param const unsigned int actorId
	*/
	virtual void VDestroyActor(const unsigned int actorId);


	/*
		@param const unsigned int actorId
		@return std::weak_ptr<Actor>
	*/
	virtual WeakActorPtr VGetActor(const unsigned int actorId);


	/*
		@parma const unsigned int actorId
		@param tinyxml2::XMLElement *overrides
	*/
	virtual void VModifyActor(const unsigned int actorId, tinyxml2::XMLElement *overrides);


	/*
		@param const unsigned int id
		@param glx::mat4<float> const &mat
	*/
	virtual void VMoveActor(const unsigned int id, glx::mat4<float> const &mat) {}

	
	/*
		Editor function

		@param const unsigned int id
		@return std::string
	*/
	std::string GetActorXml(const unsigned int id);

	/*
		@return const LevelManager*
	*/
	const LevelManager* GetLevelManager() { return m_pLevelManager; }

	/*
		Subclasses shouldn't override this function; use VLoadGameDelegate() instead

		@param const char* levelResource
		@return true if game resources were loaded successfuly, otherwise returns false
	*/
	virtual bool VLoadGame(const char* levelResource) override;

	/*
		
	*/
	virtual void VSetProxy();

	/*
		Game Logic Update

		@parma float time
		@param float elapsedTime
	*/
	virtual void VOnUpdate(float time, float elapsedTime);

	/*
		Changing Game Logic State
		@param BaseGameState newState
	*/
	virtual void VChangeState(BaseGameState newState);

	/*
		Returns current game logic state

		@return BaseGameSatate
	*/
	const BaseGameState GetState() const { return m_State; }

	/*
		
	*/
	void ToggleRenderDiagnostics() { m_RenderDiagnostics = !m_RenderDiagnostics; }

	/*
		
	*/
	virtual void VRenderDiagnostics();

	/*
		@return std::shared_ptr<IGamePhysics>
	*/
	virtual std::shared_ptr<IGamePhysics> VGetGamePhysics(void) { return m_pPhysics; }

	//void AttachProcess(StrongProcessPtr pProcess) { if (m_pProcessManager) { m_pProcessManager->AttachProcess(pProcess); } }


	// event delegates
	void RequestDestroyActorDelegate(IEventDataPtr pEventData);
protected:
	virtual ActorFactory* VCreateActorFactory(void);

	/*
		[rez] Override this function to do any game-specific loading.

		@param tinyxml2::XMLElement* pLevelData
		@return true

	*/
	virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData) { return true; }

	//void MoveActorDelegate(IEventDataPtr pEventData);
	//void RequestNewActorDelegate(IEventDataPtr pEventData);
};
#endif
