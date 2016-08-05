#ifndef _ACTOR_FACTORY_H_
#define _ACTOR_FACTORY_H_

//forward declared
class ActorComponent;


class ActorFactory
{
	unsigned int m_lastActorId;

protected:
	GenericObjectFactory<ActorComponent, unsigned int> m_componentFactory;

public:
	ActorFactory(void);

	StrongActorPtr CreateActor(const char* actorResource, tinyxml2::XMLElement* overrides, const glx::mat4<float>* initialTransform, const unsigned int serversActorId);
	void ModifyActor(StrongActorPtr pActor, tinyxml2::XMLElement* overrides);

	//protected:
	// [rez] This function can be overridden by a subclass so you can create game-specific C++ components.  If you do
	// this, make sure you call the base-class version first.  If it returns NULL, you know it's not an engine component.
	virtual StrongActorComponentPtr VCreateComponent(tinyxml2::XMLElement* pData);

private:
	unsigned int GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
};


#endif