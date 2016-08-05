#ifndef _RENDERING_COMPONENT_H_
#define _RENDERING_COMPONENT_H_

//forward declaration
class SceneNode;


#include <TywGame\Actors\RenderComponentInterface.h>



//---------------------------------------------------------------------------------------------------------------------
// RenderComponent base class.  This class does most of the work except actually creating the scene, which is 
// delegated to the subclass through a factory method:
// http://en.wikipedia.org/wiki/Factory_method_pattern
//---------------------------------------------------------------------------------------------------------------------
class BaseRenderComponent : public RenderComponentInterface
{
protected:
	glx::vec4<float> m_color;
	std::shared_ptr<SceneNode> m_pSceneNode;

public:
	virtual bool VInit(tinyxml2::XMLElement* pData) override;
	virtual void VPostInit(void) override;
	virtual void VOnChanged(void) override;
	virtual tinyxml2::XMLElement* VGenerateXml(void) override;
	const glx::vec4<float> GetColor() const { return m_color; }

protected:
	// loads the SceneNode specific data (represented in the <SceneNode> tag)
	virtual bool VDelegateInit(tinyxml2::XMLElement* pData) { return true; }
	virtual std::shared_ptr<SceneNode> VCreateSceneNode(void) = 0;  // factory method to create the appropriate scene node
	glx::vec4<float> LoadColor(tinyxml2::XMLElement* pData);

	// editor stuff
	virtual tinyxml2::XMLElement* VCreateBaseElement(void) {return nullptr;} //TYW_NEW tinyxml2::XMLElement(VGetName()); }
	virtual void VCreateInheritedXmlElements(tinyxml2::XMLElement* pBaseElement) = 0;

private:
	virtual std::shared_ptr<SceneNode> VGetSceneNode(void) override;
};


//---------------------------------------------------------------------------------------------------------------------
// This class represents a render component built from a Mesh.  In a real game, this is the one you'll use 99% of the 
// time towards the end of the project.  The other classes are important for testing since programming tends to move 
// a lot faster than art in the early stages of development.
//---------------------------------------------------------------------------------------------------------------------
class MeshRenderComponent : public BaseRenderComponent
{
public:
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

protected:
	virtual std::shared_ptr<SceneNode> VCreateSceneNode(void) override;  // factory method to create the appropriate scene node
	virtual void VCreateInheritedXmlElements(tinyxml2::XMLElement* pBaseElement);
};

#endif