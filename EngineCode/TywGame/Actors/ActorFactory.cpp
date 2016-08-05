#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\ResourceCache\XmlResource.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>


//Game Includes
#include "IGameLogic.h"
#include "Actors\ActorFactory.h"
#include "Actors\Actor.h"
#include "Actors\ActorComponent.h"
#include "Actors\TransformComponent.h"


//Renderer Includes
#include <TywRenderer\IRenderer.h>






ActorFactory::ActorFactory(void)
{
	m_lastActorId = 0;


}

StrongActorPtr ActorFactory::CreateActor(const char* actorResource, tinyxml2::XMLElement *overrides, const glx::mat4<float> *pInitialTransform, const unsigned int serversActorId)
{
	// Grab the root XML node
	tinyxml2::XMLElement* pRoot = XmlResourceLoader::LoadAndReturnRootXmlElement(actorResource);
	if (!pRoot)
	{
		//GCC_ERROR("Failed to create actor from resource: " + std::string(actorResource));
		return StrongActorPtr();
	}

	// create the actor instance
	unsigned int nextActorId = serversActorId;
	if (nextActorId == 0)
	{
		nextActorId = GetNextActorId();
	}
	StrongActorPtr pActor(TYW_NEW Actor(nextActorId));
	if (!pActor->Init(pRoot))
	{
		//GCC_ERROR("Failed to initialize actor: " + std::string(actorResource));
		return StrongActorPtr();
	}

	bool initialTransformSet = false;

	// Loop through each child element and load the component
	for (tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		StrongActorComponentPtr pComponent(VCreateComponent(pNode));
		if (pComponent)
		{
			pActor->AddComponent(pComponent);
			pComponent->SetOwner(pActor);
		}
		else
		{
			// If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be 
			// partially complete so it's not worth it.  Note that the pActor instance will be destroyed because it
			// will fall out of scope with nothing else pointing to it.
			return StrongActorPtr();
		}
	}

	if (overrides)
	{
		ModifyActor(pActor, overrides);
	}

	// This is a bit of a hack to get the initial transform of the transform component set before the 
	// other components (like PhysicsComponent) read it.
	std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
	if (pInitialTransform && pTransformComponent)
	{
		pTransformComponent->SetPosition(pInitialTransform->GetPosition());
	}

	// Now that the actor has been fully created, run the post init phase
	pActor->PostInit();

	return pActor;
}

StrongActorComponentPtr ActorFactory::VCreateComponent(tinyxml2::XMLElement* pData)
{
	const char* name = pData->Value();
	StrongActorComponentPtr pComponent(m_componentFactory.Create(ActorComponent::GetIdFromName(name)));

	// initialize the component if we found one
	if (pComponent)
	{
		if (!pComponent->VInit(pData))
		{
			//GCC_ERROR("Component failed to initialize: " + std::string(name));
			return StrongActorComponentPtr();
		}
	}
	else
	{
		//GCC_ERROR("Couldn't find ActorComponent named " + std::string(name));
		return StrongActorComponentPtr();  // fail
	}

	// pComponent will be NULL if the component wasn't found.  This isn't necessarily an error since you might have a 
	// custom CreateComponent() function in a sub class.
	return pComponent;
}


void ActorFactory::ModifyActor(StrongActorPtr pActor, tinyxml2::XMLElement* overrides)
{
	// Loop through each child element and load the component
	for (tinyxml2::XMLElement* pNode = overrides->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		unsigned int componentId = ActorComponent::GetIdFromName(pNode->Value());
		StrongActorComponentPtr pComponent; //= MakeStrongPtr(pActor->GetComponent<ActorComponent>(componentId));
		if (pComponent)
		{
			pComponent->VInit(pNode);

			// [mrmike] - added post press to ensure that components that need it have
			//            Events generated that can notify subsystems when changes happen.
			//            This was done to have SceneNode derived classes respond to RenderComponent
			//            changes.

			pComponent->VOnChanged();
		}
		else
		{
			pComponent = VCreateComponent(pNode);
			if (pComponent)
			{
				pActor->AddComponent(pComponent);
				pComponent->SetOwner(pActor);
			}
		}
	}
}