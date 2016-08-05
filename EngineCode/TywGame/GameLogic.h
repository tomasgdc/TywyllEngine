#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "BaseGameLogic.h"



class GameLogic : public BaseGameLogic
{
protected:
//	std::list<NetworkEventForwarder*> m_networkEventForwarders;

public:
	GameLogic();
	virtual ~GameLogic();


	/*******************************************
					UPDATE
	*******************************************/

	/*

	*/
	virtual void VSetProxy();

	/*
		@param const unsigned int actorId
		@parma const glx::mat4<float> &mat
	*/
	virtual void VMoveActor(const unsigned int actorId, const glx::mat4<float> &mat);

	/**/
	//Overloads

	/*
		@param BaseGameState
	*/
	virtual void VChangeState(BaseGameState newState);

	/*
		@param std::shared_ptr<IGameView> pView
		@param unsigned int actorId
	*/
	virtual void VAddView(std::shared_ptr<IGameView> pView, unsigned int actorId = 0);

	/*
		@return std::shared_ptr<IGamePhysics>
	*/
	virtual std::shared_ptr<IGamePhysics> VGetGamePhysics(void) { return m_pPhysics; }


	/*******************************************
				EVENT DELEGATES
	*******************************************/

	/*
		@param IEventDataPtr pEventData
	*/
	void RequestStartGameDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void RemoteClientDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void NetworkPlayerActorAssignmentDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void EnvironmentLoadedDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void ThrustDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void SteerDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void StartThrustDelegate(IEventDataPtr pEventData);

	/*
		@parma IEventDataPtr pEventData
	*/
	void EndThrustDelegate(IEventDataPtr pEventData);

	/*
		@parma IEventDataPtr pEventData
	*/
	void StartSteerDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void EndSteerDelegate(IEventDataPtr pEventData);

	/*
		@param IEventDataPtr pEventData
	*/
	void TestScriptDelegate(IEventDataPtr pEventData);

protected:
	/*
		@param tinyxml2::XMLElement* pLevelData
		@return bool
	*/
	virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData);

private:
	void RegisterAllDelegates(void);
	void RemoveAllDelegates(void);
	void CreateNetworkEventForwarder(const int socketId);
	void DestroyAllNetworkEventForwarders(void);
};

#endif