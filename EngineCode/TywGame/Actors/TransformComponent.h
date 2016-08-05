#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include "Actors\ActorComponent.h"


class TransformComponent : public ActorComponent
{
	glx::mat4<float> m_transform;
public:
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	TransformComponent(void) : m_transform() { }
	virtual bool VInit(tinyxml2::XMLElement* pData) override;
	virtual tinyxml2::XMLElement* VGenerateXml(void) override;

	// transform functions
	glx::mat4<float> GetTransform(void) const { return m_transform; }
	void SetTransform(const glx::mat4<float>& newTransform) { m_transform = newTransform; }
	glx::vec3<float> GetPosition(void) const { return m_transform.GetPosition(); }
	void SetPosition(const glx::vec3<float>& pos) { m_transform.SetPosition(pos); }
	//glx::vec3<float> GetLookAt(void) const { return m_transform.GetDirection(); }
};

#endif