//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#include <stdafx.h>
#include <TywLib\math\GLXMath.h>
#include <TywLib\geometry\JointTransform.h>
#include <TywLib\geometry\VertData.h>


//Engine Includes
#include <TywEngine\EventManager\IEventManager.h>


//Renderer Includes
#include "OpenGL\Texture2D.h"
#include "GLRenderer.h"
#include "Lights.h"
#include "SceneManager.h"


LightNode::LightNode(const ActorId actorId, WeakBaseRenderComponentPtr renderComponent, const LightProperties &props, const glx::mat4<float> *t)
	:SceneNode(actorId, renderComponent, RenderPass_NotRendered, t)
{
	m_LightProps = props;
}



void LightManager::CalcLighting(SceneManager *pScene)
{
	// FUTURE WORK: There might be all kinds of things you'd want to do here for optimization, especially turning off lights on actors that can't be seen, etc.
	pScene->GetRenderer()->VCalcLighting(&m_Lights, MAXIMUM_LIGHTS_SUPPORTED);

	int count = 0;

	assert(m_Lights.size() < MAXIMUM_LIGHTS_SUPPORTED);
	for (Lights::iterator i = m_Lights.begin(); i != m_Lights.end(); ++i, ++count)
	{
		std::shared_ptr<LightNode> light = *i;

		if (count == 0)
		{
			// Light 0 is the only one we use for ambient lighting. The rest are ignored in the simple shaders used for GameCode4.
			//glx::vec4<float> ambient = light->VGet()->GetMaterial();
			//m_vLightAmbient = D3DXVECTOR4(ambient.r, ambient.g, ambient.b, 1.0f);
		}

		glx::vec3<float> lightDir = light->GetDirection();
		//m_vLightDir[count] = D3DXVECTOR4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
		//m_vLightDiffuse[count] = light->VGet()->GetMaterial().GetDiffuse();
	}
}


void LightManager::CalcLighting(ConstantBuffer_Lighting* pLighting, SceneNode *pNode)
{
	int count = GetLightCount(pNode);
	if (count)
	{
		pLighting->m_vLightAmbient = *GetLightAmbient(pNode);
		memcpy(pLighting->m_vLightDir, GetLightDirection(pNode), sizeof(glx::vec4<float>) * count);
		memcpy(pLighting->m_vLightDiffuse, GetLightDiffuse(pNode), sizeof(glx::vec4<float>) * count);
		pLighting->m_nNumLights = count;
	}
}

