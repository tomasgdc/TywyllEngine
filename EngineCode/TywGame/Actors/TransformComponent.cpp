#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\utilities\templates.h>
#include <TywLib\utilities\EngineString.h>
#include <TywLib\utilities\EngineVariables.h>

//Game Includes
#include "IGameLogic.h"
#include "TransformComponent.h"


const char* TransformComponent::g_Name = "TransformComponent";



bool TransformComponent::VInit(tinyxml2::XMLElement* pData)
{
	assert(pData);

	// [mrmike] - this was changed post-press - because changes to the TransformComponents can come in partial definitions,
	//            such as from the editor, its better to grab the current values rather than clear them out.

	glx::vec3<float> yawPitchRoll = GLXGetYawPitchRoll(m_transform);
	yawPitchRoll.x = RADIANS_TO_DEGREES(yawPitchRoll.x);
	yawPitchRoll.y = RADIANS_TO_DEGREES(yawPitchRoll.y);
	yawPitchRoll.z = RADIANS_TO_DEGREES(yawPitchRoll.z);

	glx::vec3<float> position = m_transform.GetPosition();

	tinyxml2::XMLElement* pPositionElement = pData->FirstChildElement("Position");
	if (pPositionElement)
	{
		double x = 0;
		double y = 0;
		double z = 0;
		pPositionElement->QueryDoubleAttribute("x", &x);
		pPositionElement->QueryDoubleAttribute("y", &y);
		pPositionElement->QueryDoubleAttribute("z", &z);
		position = glx::vec3<float>(x, y, z);
	}

	tinyxml2::XMLElement* pOrientationElement = pData->FirstChildElement("YawPitchRoll");
	if (pOrientationElement)
	{
		double yaw = 0;
		double pitch = 0;
		double roll = 0;
		pOrientationElement->QueryDoubleAttribute("x", &yaw);
		pOrientationElement->QueryDoubleAttribute("y", &pitch);
		pOrientationElement->QueryDoubleAttribute("z", &roll);
		yawPitchRoll = glx::vec3<float>(yaw, pitch, roll);
	}

	glx::mat4<float> translation;
	GLXMatrixIdentity(&translation);
	translation.SetPosition(position);

	glx::mat4<float> rotation;
	GLXBuildYawPitchRoll(rotation, (float)DEGREES_TO_RADIANS(yawPitchRoll.x), (float)DEGREES_TO_RADIANS(yawPitchRoll.y), (float)DEGREES_TO_RADIANS(yawPitchRoll.z));

	/**
	// This is not supported yet.
	TiXmlElement* pLookAtElement = pData->FirstChildElement("LookAt");
	if (pLookAtElement)
	{
	double x = 0;
	double y = 0;
	double z = 0;
	pLookAtElement->Attribute("x", &x);
	pLookAtElement->Attribute("y", &y);
	pLookAtElement->Attribute("z", &z);

	Vec3 lookAt((float)x, (float)y, (float)z);
	rotation.BuildRotationLookAt(translation.GetPosition(), lookAt, g_Up);
	}

	TiXmlElement* pScaleElement = pData->FirstChildElement("Scale");
	if (pScaleElement)
	{
	double x = 0;
	double y = 0;
	double z = 0;
	pScaleElement->Attribute("x", &x);
	pScaleElement->Attribute("y", &y);
	pScaleElement->Attribute("z", &z);
	m_scale = Vec3((float)x, (float)y, (float)z);
	}
	**/

	m_transform = rotation * translation;

	return true;
}

tinyxml2::XMLElement* TransformComponent::VGenerateXml(void)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLElement* pBaseElement = xmlDoc.NewElement(VGetName());

	// initial transform -> position
	tinyxml2::XMLElement* pPosition = xmlDoc.NewElement("Position");
	glx::vec3<float> pos(m_transform.GetPosition());
	pPosition->SetAttribute("x", ToStr(pos.x).c_str());
	pPosition->SetAttribute("y", ToStr(pos.y).c_str());
	pPosition->SetAttribute("z", ToStr(pos.z).c_str());
	pBaseElement->LinkEndChild(pPosition);

	// initial transform -> LookAt
	tinyxml2::XMLElement* pDirection = xmlDoc.NewElement("YawPitchRoll");
	glx::vec3<float> orient(GLXGetYawPitchRoll(m_transform));
	orient.x = RADIANS_TO_DEGREES(orient.x);
	orient.y = RADIANS_TO_DEGREES(orient.y);
	orient.z = RADIANS_TO_DEGREES(orient.z);
	pDirection->SetAttribute("x", ToStr(orient.x).c_str());
	pDirection->SetAttribute("y", ToStr(orient.y).c_str());
	pDirection->SetAttribute("z", ToStr(orient.z).c_str());
	pBaseElement->LinkEndChild(pDirection);

	/***
	// This is not supported yet
	// initial transform -> position
	TiXmlElement* pScale = GCC_NEW TiXmlElement("Scale");
	pPosition->SetAttribute("x", ToStr(m_scale.x).c_str());
	pPosition->SetAttribute("y", ToStr(m_scale.y).c_str());
	pPosition->SetAttribute("z", ToStr(m_scale.z).c_str());
	pBaseElement->LinkEndChild(pScale);
	**/
	return pBaseElement;
}