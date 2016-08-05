#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\EngineVariables.h>
#include <TywLib\utilities\EngineString.h>

//Game Includes
#include "RenderingComponent.h"

//Engine Includes
#include <TywEngine\EventManager\Events.h>
#include <TywEngine\EventManager\EventManagerImpl.h>


//Renderer Includes
#include <TywRenderer\IRenderer.h>
#include <TywRenderer\SceneNode.h>





//-------------------------------------------------------------------------------------------------------------------- -
// RenderComponent
//---------------------------------------------------------------------------------------------------------------------
bool BaseRenderComponent::VInit(tinyxml2::XMLElement* pData)
{
	// color
	tinyxml2::XMLElement* pColorNode = pData->FirstChildElement("Color");
	if (pColorNode)
		//m_color = LoadColor(pColorNode);

	return VDelegateInit(pData);
}

void BaseRenderComponent::VPostInit(void)
{
	std::shared_ptr<SceneNode> pSceneNode(VGetSceneNode());
	//std::shared_ptr<EvtData_New_Render_Component> pEvent(TYW_NEW EvtData_New_Render_Component(m_pOwner->GetId(), pSceneNode));
	//IEventManager::GetInstance()->VTriggerEvent(pEvent);
}


void BaseRenderComponent::VOnChanged(void)
{
	//std::shared_ptr<EvtData_Modified_Render_Component> pEvent(TYW_NEW EvtData_Modified_Render_Component(m_pOwner->GetId()));
	//IEventManager::GetInstance()->VTriggerEvent(pEvent);
}


tinyxml2::XMLElement* BaseRenderComponent::VGenerateXml(void)
{
	tinyxml2::XMLElement* pBaseElement = VCreateBaseElement();

	// color
	/*
	tinyxml2::XMLElement* pColor = TYW_NEW TiXmlElement("Color");
	pColor->SetAttribute("r", ToStr(m_color.x).c_str());
	pColor->SetAttribute("g", ToStr(m_color.y).c_str());
	pColor->SetAttribute("b", ToStr(m_color.z).c_str());
	pColor->SetAttribute("a", ToStr(m_color.w).c_str());
	pBaseElement->LinkEndChild(pColor);
	*/

	// create XML for inherited classes
	VCreateInheritedXmlElements(pBaseElement);

	return pBaseElement;
}

std::shared_ptr<SceneNode> BaseRenderComponent::VGetSceneNode(void)
{
	if (!m_pSceneNode)
		m_pSceneNode = VCreateSceneNode();
	return m_pSceneNode;
}

glx::vec4<float> BaseRenderComponent::LoadColor(tinyxml2::XMLElement* pData)
{
	glx::vec4<float> color;

	pData->QueryFloatAttribute("r", &color.x);
	pData->QueryFloatAttribute("g", &color.y);
	pData->QueryFloatAttribute("b", &color.z);
	pData->QueryFloatAttribute("a", &color.w);
	return color;
}


//---------------------------------------------------------------------------------------------------------------------
// MeshRenderComponent
//---------------------------------------------------------------------------------------------------------------------
std::shared_ptr<SceneNode> MeshRenderComponent::VCreateSceneNode(void)
{
	return std::shared_ptr<SceneNode>();
}

void MeshRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement *)
{
	//("MeshRenderComponent::VGenerateSubclassXml() not implemented");
}