#ifndef _RENDER_COMPONENT_INTERFACE_H_
#define _RENDER_COMPONENT_INTERFACE_H_

#include "ActorComponent.h"

class RenderComponentInterface : public ActorComponent
{
public:
	//    virtual ComponentId VGetComponentId(void) const override { return COMPONENT_ID; }

	// RenderComponentInterface
	virtual std::shared_ptr<SceneNode> VGetSceneNode(void) = 0;
};



#endif

