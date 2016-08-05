#ifndef _ACTOR_H_
#define _ACTOR_H_

class tinyxml2::XMLElement;
typedef std::string ActorType;

//---------------------------------------------------------------------------------------------------------------------
// Actor class
// Chapter 6, page 165
//---------------------------------------------------------------------------------------------------------------------
class Actor
{
	friend class ActorFactory;

public:

	typedef std::map<unsigned int, StrongActorComponentPtr> ActorComponents;

private:
	unsigned int m_id;					// unique id for the actor
	ActorComponents m_components;	// all components this actor has
	ActorType m_type;

	// [mrmike] - these were added post press as editor helpers, but will also be great for save game files if we ever make them.
	std::string m_resource;			// the XML file from which this actor was initialized (considered the "Archetype" file)

public:
	explicit Actor(unsigned int id);
	~Actor(void);

	
	bool Init(tinyxml2::XMLElement* pData);
	void PostInit(void);
	void Destroy(void);
	void Update(int deltaMs);

	// editor functions
	//bool SaveActorFromEditor(const char* path);      //[mrmike] - we can delete this.
	std::string Actor::ToXML();

	// accessors
	unsigned int GetId(void) const { return m_id; }
	ActorType GetType(void) const { return m_type; }

	// template function for retrieving components
	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent(unsigned int id)
	{
		ActorComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongActorComponentPtr pBase(findIt->second);
			std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}

	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent(const char *name)
	{
		unsigned int id = ActorComponent::GetIdFromName(name);
		ActorComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongActorComponentPtr pBase(findIt->second);
			std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}

	const ActorComponents* GetComponents() { return &m_components; }

	void AddComponent(StrongActorComponentPtr pComponent);
};


#endif