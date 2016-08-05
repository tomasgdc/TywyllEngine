#ifndef _ENGINE_VARIABLES_H_
#define _ENGINE_VARIABLES_H_

//Game Specific Variables
class Actor;
class ActorComponent;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef std::weak_ptr<ActorComponent> WeakActorComponentPtr;

#endif