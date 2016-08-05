#ifndef _I_GAME_LOGIC_H_
#define _I_GAME_LOGIC_H_


//forward declared
class Actor;
class ActorComponent;
class IGamePhysics;



class IGameLogic
{
public:
	IGameLogic() {}
	virtual ~IGameLogic() {}


	virtual WeakActorPtr VGetActor(const unsigned int id) = 0;
	//virtual StrongActorPtr VCreateActor(const std::string &actorResource, TiXmlElement *overrides, const glx::mat4<float> *initialTransform = nullptr, const ActorId serversActorId = INVALID_ACTOR_ID) = 0;


	virtual void VDestroyActor(const unsigned int actorId) = 0;
	virtual bool VLoadGame(const char* levelResource) = 0;
	virtual void VSetProxy() = 0;
	virtual void VOnUpdate(float time, float elapsedTime) = 0;
	virtual void VChangeState(enum class BaseGameState newState) = 0;
	virtual void VMoveActor(const unsigned int id, glx::mat4<float> const &mat) = 0;
	virtual std::shared_ptr<IGamePhysics> VGetGamePhysics(void) = 0;
};
#endif
