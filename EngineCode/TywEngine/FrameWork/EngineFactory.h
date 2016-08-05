//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.
#pragma once


// Singleton factory
template <class I>
class EngineFactory
{
public:
	/**
	* Return singleton instance of factory class.
	*/
	static EngineFactory<I>& Instance()
	{
		static EngineFactory<I> instance;
		return instance;
	}

	/**
	* Register a named object constructor.
	* @param strName The name of the object type.
	* @param fnConstructor The constructor function for the object, usually a
	* lambda.
	*/
	void AddConstructor(uint16_t iId, std::function<std::shared_ptr<I>(void)> fnConstructor)
	{
		m_mapConstructors[iId] = fnConstructor;
	}

	/**
	* Construct an object of the named type.
	* Attempts to find the constructor for the named type, if not found attempts
	* to find a 'default' constructor and if still not found throws an exception.
	* @param strName The name of the object type to construct.
	*/
	std::shared_ptr<I> Construct(uint16_t iId)
	{
		if (m_mapConstructors.find(iId) != m_mapConstructors.end())
		{
			return m_mapConstructors[strName]();
		}
		// TODO: Could locate matching shared library and load it
		return nullptr;
	}

	typename std::map<uint16_t, std::function<std::shared_ptr<I>(void)>>::iterator begin()
	{
		return m_mapConstructors.begin();
	}

	typename std::map<uint16_t, std::function<std::shared_ptr<I>(void)>>::iterator end()
	{
		return m_mapConstructors.end();
	}

	typename std::map<uint16_t, std::function<std::shared_ptr<I>(void)>>::iterator cbegin() const
	{
		return m_mapConstructors.cbegin();
	}

	typename std::map<uint16_t, std::function<std::shared_ptr<I>(void)>>::iterator cend() const
	{
		return m_mapConstructors.cend();
	}

private:
	/**
	* Private constructor and destructor to prevent creation and destruction
	* other than by the Instance() method.
	*/
	EngineFactory<I>() {};
	~EngineFactory<I>() {};

	/**
	* Deleted the copy and assignement constructors.
	*/
	EngineFactory<I>(EngineFactory<I> const&);
	void operator=(EngineFactory<I> const&);

private:
	/**
	* Collection of callable named object constructors.
	*/
	std::map<uint16_t, std::function<std::shared_ptr<I>(void)>> m_mapConstructors;
};

/**
* Macro to register a new object type with different id and concrete type.
*/
#define REGISTER(id, iface, type) \
    EngineFactory<iface>::Instance().AddConstructor(id, []()->std::shared_ptr<iface>{return std::shared_ptr<iface> (new type());});


/**
* Macro to construct an object by id.
*/
#define CONSTRUCT(iface, id) \
    EngineFactory<iface>::Instance().Construct(id) // Note the lack of semi-colon


/**
* Macro to get the instance of the factory for an interface.
*/
#define FACTORY_INSTANCE(iface) \
    EngineFactory<iface>::Instance() // Note the lack of semi-colon
