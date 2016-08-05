#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>


//Game Includes
#include "IGameLogic.h"
#include "Actors/Actor.h"
#include "Actors\ActorComponent.h"

//Renderer Includes



//---------------------------------------------------------------------------------------------------------------------
// Actor
// Chapter 6, page 165
//---------------------------------------------------------------------------------------------------------------------
Actor::Actor(unsigned int id)
{
	m_id = id;
	m_type = "Unknown";

	// [mrmike] added post press - this is an editor helper
	m_resource = "Unknown";
}

Actor::~Actor(void)
{
	//GCC_LOG("Actor", std::string("Destroying Actor ") + ToStr(m_id));
	//GCC_ASSERT(m_components.empty());  // [rez] if this assert fires, the actor was destroyed without calling Actor::Destroy()
}

bool Actor::Init(tinyxml2::XMLElement* pData)
{
	//GCC_LOG("Actor", std::string("Initializing Actor ") + ToStr(m_id));


	m_type = pData->Attribute("type");
	m_resource = pData->Attribute("resource");
	return true;
}

void Actor::PostInit(void)
{
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->VPostInit();
	}
}

void Actor::Destroy(void)
{
	m_components.clear();
}

void Actor::Update(int deltaMs)
{
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->VUpdate(deltaMs);
	}
}

std::string Actor::ToXML()
{
	tinyxml2::XMLDocument outDoc;

	// Actor element
	tinyxml2::XMLElement* pActorElement = outDoc.NewElement("Actor");
	pActorElement->SetAttribute("type", m_type.c_str());
	pActorElement->SetAttribute("resource", m_resource.c_str());

	// components
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		StrongActorComponentPtr pComponent = it->second;
		tinyxml2::XMLElement* pComponentElement = pComponent->VGenerateXml();
		pActorElement->LinkEndChild(pComponentElement);
	}

	outDoc.LinkEndChild(pActorElement);
	tinyxml2::XMLPrinter printer;
	outDoc.Accept(&printer);

	return printer.CStr();
}


void Actor::AddComponent(StrongActorComponentPtr pComponent)
{
	//std::pair<ActorComponents::iterator, bool> success = m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
	//GCC_ASSERT(success.second);
}