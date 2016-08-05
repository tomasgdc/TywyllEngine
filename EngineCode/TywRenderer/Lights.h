#ifndef _LIGHTS_H_
#define _LIGHTS_H_
#include "SceneNode.h"


/*
	Light properties
*/
struct TYWRENDERER_API LightProperties
{
	float	m_Attenuation[3];  /* Attenuation coefficients */
	float	m_Range;
	float	m_Falloff;
	float	m_Theta;
	float	m_Phi;
};


/*
	Light node
*/
class TYWRENDERER_API LightNode : public SceneNode
{
protected:
	LightProperties m_LightProps;

public:
	LightNode(const ActorId actorId, WeakBaseRenderComponentPtr renderComponent, const LightProperties &props, const glx::mat4<float> *t);
};


typedef std::vector<std::shared_ptr<LightNode> > Lights;	//list of lights
struct ConstantBuffer_Lighting;


/*
	LightManager contains all lights in the game
	and calculates lights for scene
*/
class TYWRENDERER_API LightManager
{
	friend class SceneManager;

protected:
	Lights					m_Lights;
	glx::vec4<float>		m_vLightDir[MAXIMUM_LIGHTS_SUPPORTED];
	glx::vec4<float>		m_vLightDiffuse[MAXIMUM_LIGHTS_SUPPORTED];
	glx::vec4<float>		m_vLightAmbient;

public:
	void CalcLighting(SceneManager *pScene);
	void CalcLighting(ConstantBuffer_Lighting* pLighting, SceneNode *pNode);
	int GetLightCount(const SceneNode *node) { return m_Lights.size(); }
	const glx::vec4<float> *GetLightAmbient(const SceneNode *node) { return &m_vLightAmbient; }
	const glx::vec4<float> *GetLightDirection(const SceneNode *node) { return m_vLightDir; }
	const glx::vec4<float> *GetLightDiffuse(const SceneNode *node) { return m_vLightDiffuse; }
};
#endif