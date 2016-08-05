#pragma once

#include <TywEngine\LuaScripting\ScriptEvent.h>



class EvtData_Fire_Weapon : public ScriptEvent
{
	uint32_t m_id;

public:
	static const EventType sk_EventType;
	virtual const EventType & VGetEventType() const
	{
		return sk_EventType;
	}

	EvtData_Fire_Weapon(void)
	{
		m_id = 0;
	}

	EvtData_Fire_Weapon(uint32_t id)
		: m_id(id)
	{
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_Fire_Weapon(m_id));
	}

	virtual void VSerialize(std::ostrstream & out) const
	{
		out << m_id << " ";
	}

	virtual void VDeserialize(std::istrstream & in)
	{
		in >> m_id;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_Fire_Weapon";
	}

	virtual bool VBuildEventFromScript(void)
	{
			// ID
			sol::object temp = m_eventData["id"];
			if (temp.is<int>())
			{
				m_id = m_eventData.get<int>("id");
			}
			else
			{
				fprintf(stdout, "Invalid id sent to EvtData_Fire_Weapon; type = %s"); // std::string(temp.TypeName()));
				return false;
			}
			return true;
	}

	uint32_t GetActorId(void) const
	{
		return m_id;
	}

	virtual void VBuildEventData(void);

	EXPORT_FOR_SCRIPT_EVENT(EvtData_Fire_Weapon);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_StartThrust				        - Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_StartThrust : public ScriptEvent
{
	uint32_t m_id;
	float m_acceleration;

public:
	static const EventType sk_EventType;
	virtual const EventType& VGetEventType(void) const
	{
		return sk_EventType;
	}

	EvtData_StartThrust(void) :
		m_id(0),
		m_acceleration(0)
	{
		//
	}

	EvtData_StartThrust(uint32_t id, float acceleration) :
		m_id(id),
		m_acceleration(acceleration)
	{
		//
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_StartThrust(m_id, m_acceleration));
	}

	virtual void VSerialize(std::ostrstream & out) const
	{
		out << m_id << " ";
		out << m_acceleration << " ";
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_id;
		in >> m_acceleration;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_ThrustStart";
	}

	uint32_t GetActorId(void) const
	{
		return m_id;
	}

	float GetAcceleration(void) const
	{
		return m_acceleration;
	}

	void Set(uint32_t id)
	{
		m_id = id;
	}

	virtual bool VBuildEventFromScript(void)
	{
			// ID
			sol::object temp = m_eventData["id"];
			if (temp.is<int>())
			{
				m_id = m_eventData.get<int>("id");
			}
			else
			{
				fprintf(stdout, "Invalid id sent to EvtData_StartThrust; type = %s");// std::string(temp.TypeName())); //TEST
				return false;
			}

			// acceleration
			temp = m_eventData["acceleration"];
			if (temp.is<float>())
				m_acceleration = m_eventData.get<float>("acceleration");
			else
				m_acceleration = 5.0f;  // something reasonable

			return true;
	}

	EXPORT_FOR_SCRIPT_EVENT(EvtData_StartThrust);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_EndThrust				        - Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_EndThrust : public ScriptEvent
{
	uint32_t m_id;

public:
	static const EventType sk_EventType;
	virtual const EventType & VGetEventType(void) const
	{
		return sk_EventType;
	}

	EvtData_EndThrust(void) :
		m_id(0)
	{
		//
	}

	EvtData_EndThrust(uint32_t id) :
		m_id(id)
	{
		//
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_EndThrust(m_id));
	}

	virtual void VSerialize(std::ostrstream & out) const
	{
		out << m_id << " ";
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_id;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_EndThrust";
	}

	uint32_t GetActorId(void) const
	{
		return m_id;
	}

	void Set(uint32_t id)
	{
		m_id = id;
	}

	virtual bool VBuildEventFromScript(void)
	{
			// ID
			sol::object temp = m_eventData["id"];
			if (temp.is<int>())
			{
				m_id = m_eventData.get<int>("id");
			}
			else
			{
				fprintf(stdout, "Invalid id sent to EvtData_EndThrust; type = %s"); // std::string(temp.get_type()); //test
				return false;
			}
			return true;
	}

	EXPORT_FOR_SCRIPT_EVENT(EvtData_EndThrust);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_StartSteer				             - Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_StartSteer : public ScriptEvent
{
	uint32_t m_id;
	float m_acceleration;

public:
	static const EventType sk_EventType;
	virtual const EventType & VGetEventType(void) const
	{
		return sk_EventType;
	}

	EvtData_StartSteer(void) :
		m_id(0),
		m_acceleration(0)
	{
		//
	}

	EvtData_StartSteer(uint32_t id, float acceleration) :
		m_id(id),
		m_acceleration(acceleration)
	{
		//
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_StartSteer(m_id, m_acceleration));
	}

	virtual void VSerialize(std::ostrstream & out) const
	{
		out << m_id << " ";
		out << m_acceleration << " ";
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_id;
		in >> m_acceleration;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_StartSteer";
	}

	uint32_t GetActorId(void) const
	{
		return m_id;
	}

	float GetAcceleration(void) const
	{
		return m_acceleration;
	}

	void Set(uint32_t id)
	{
		m_id = id;
	}

	virtual bool VBuildEventFromScript(void)
	{
			// ID
			sol::object temp = m_eventData["id"];
			if (temp.is<int>())
			{
				m_id = m_eventData.get<int>("id");
			}
			else
			{
				fprintf(stdout, "Invalid id sent to EvtData_StartSteer; type = %s"); // std::string(temp.TypeName())); //test
				return false;
			}

			// acceleration
			temp = m_eventData["acceleration"];
			if (temp.is<float>())
				m_acceleration = m_eventData.get<float>("acceleration");
			else
				m_acceleration = 5.0f;  // something reasonable

			return true;
	}
	EXPORT_FOR_SCRIPT_EVENT(EvtData_StartSteer);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_EndSteer				        - Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_EndSteer : public ScriptEvent
{
	uint32_t m_id;

public:
	static const EventType sk_EventType;
	virtual const EventType & VGetEventType(void) const
	{
		return sk_EventType;
	}

	EvtData_EndSteer(void) :
		m_id(0)
	{
		//
	}

	EvtData_EndSteer(uint32_t id) :
		m_id(id)
	{
		//
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_EndThrust(m_id));
	}

	virtual void VSerialize(std::ostrstream & out) const
	{
		out << m_id << " ";
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_id;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_EndThrust";
	}

	uint32_t GetActorId(void) const
	{
		return m_id;
	}

	void Set(uint32_t id)
	{
		m_id = id;
	}

	virtual bool VBuildEventFromScript(void)
	{
			// ID
			sol::object temp = m_eventData["id"];
			if (temp.is<int>())
			{
				m_id = m_eventData.get<int>("id");
			}
			else
			{
				fprintf(stdout, "Invalid id sent to EvtData_EndSteer; type = %s"); // std::string(temp.TypeName())); //test
				return false;
			}

			return true;
	}

	EXPORT_FOR_SCRIPT_EVENT(EvtData_EndSteer);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_Gameplay_UI_Update				- Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_Gameplay_UI_Update : public ScriptEvent
{
	std::string m_gameplayUiString;

public:
	static const EventType sk_EventType;

	EvtData_Gameplay_UI_Update(void) { }
	EvtData_Gameplay_UI_Update(const std::string& gameplayUiString)
		: m_gameplayUiString(gameplayUiString)
	{
	}

	virtual const EventType& VGetEventType(void) const
	{
		return sk_EventType;
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_Gameplay_UI_Update(m_gameplayUiString));
	}

	virtual void VSerialize(std::ostrstream& out) const
	{
		out << m_gameplayUiString;
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_gameplayUiString;
	}

	const std::string& GetUiString(void) const
	{
		return m_gameplayUiString;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_Gameplay_UI_Update";
	}

	virtual bool VBuildEventFromScript(void);

	EXPORT_FOR_SCRIPT_EVENT(EvtData_Gameplay_UI_Update);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_Set_Controlled_Actor				- Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_Set_Controlled_Actor : public ScriptEvent
{
	uint32_t m_id;

public:
	static const EventType sk_EventType;

	EvtData_Set_Controlled_Actor(void) { }
	EvtData_Set_Controlled_Actor(uint32_t actorId)
		: m_id(actorId)
	{
	}

	virtual const EventType& VGetEventType(void) const
	{
		return sk_EventType;
	}

	virtual IEventDataPtr VCopy() const
	{
		return IEventDataPtr(TYW_NEW EvtData_Set_Controlled_Actor(m_id));
	}

	virtual void VSerialize(std::ostrstream& out) const
	{
		out << m_id;
	}

	virtual void VDeserialize(std::istrstream& in)
	{
		in >> m_id;
	}

	const uint32_t& GetActorId(void) const
	{
		return m_id;
	}

	virtual const char* GetName(void) const
	{
		return "EvtData_Set_Controlled_Actor";
	}

	virtual bool VBuildEventFromScript(void);

	EXPORT_FOR_SCRIPT_EVENT(EvtData_Set_Controlled_Actor);
};


//---------------------------------------------------------------------------------------------------------------------
// class EvtData_ScriptEventTest				             - Chapter 10, 279
//---------------------------------------------------------------------------------------------------------------------
class EvtData_ScriptEventTest_ToLua : public ScriptEvent
{
	int m_num;

public:
	static const EventType sk_EventType;

	EvtData_ScriptEventTest_ToLua(void) { m_num = 0; }
	EvtData_ScriptEventTest_ToLua(int num) { m_num = num; }

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const
	{
		std::shared_ptr<EvtData_ScriptEventTest_ToLua> pCopy(TYW_NEW EvtData_ScriptEventTest_ToLua(m_num));
		//pCopy->m_eventData = m_eventData;
		return pCopy;
	}

	virtual const char* GetName(void) const { return "EvtData_ScriptEventTest_ToLua"; }

protected:
	virtual void VBuildEventData(void);
	//virtual bool VBuildEventFromScript(void);

	EXPORT_FOR_SCRIPT_EVENT(EvtData_ScriptEventTest_ToLua);
};

class EvtData_ScriptEventTest_FromLua : public ScriptEvent
{
	int m_num;

public:
	static const EventType sk_EventType;

	EvtData_ScriptEventTest_FromLua(void) { m_num = 0; }
	EvtData_ScriptEventTest_FromLua(int num) { m_num = num; }

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const
	{
		std::shared_ptr<EvtData_ScriptEventTest_FromLua> pCopy(TYW_NEW EvtData_ScriptEventTest_FromLua(m_num));
		//pCopy->m_eventData = m_eventData;
		return pCopy;
	}

	virtual const char* GetName(void) const { return "EvtData_ScriptEventTest_FromLua"; }

	int GetNum(void) { return m_num; }

protected:
	//virtual void VBuildEventData(void);
	virtual bool VBuildEventFromScript(void);

	EXPORT_FOR_SCRIPT_EVENT(EvtData_ScriptEventTest_FromLua);
};


void RegisterGameEvents(void);
