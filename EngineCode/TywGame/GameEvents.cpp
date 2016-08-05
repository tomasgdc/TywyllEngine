#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Game Includes
#include "GameEvents.h"


//Engine Includes
#include <TywEngine\LuaScripting\LuaStateManager.h>
#include <TywEngine\FrameWork\EngineSubsystems.h>



const EventType EvtData_Fire_Weapon::sk_EventType(0x1b15b6a7);
const EventType EvtData_StartThrust::sk_EventType(0x1d62d48c);
const EventType EvtData_EndThrust::sk_EventType(0xe60f88a4);
const EventType EvtData_StartSteer::sk_EventType(0xf0b5b4fd);
const EventType EvtData_EndSteer::sk_EventType(0x176645ef);
const EventType EvtData_Gameplay_UI_Update::sk_EventType(0x1002ded2);
const EventType EvtData_Set_Controlled_Actor::sk_EventType(0xbe5e3388);
const EventType EvtData_ScriptEventTest_ToLua::sk_EventType(0x56cff2bc);
const EventType EvtData_ScriptEventTest_FromLua::sk_EventType(0x53fbab61);



bool EvtData_Gameplay_UI_Update::VBuildEventFromScript(void)
{

		//m_gameplayUiString = m_eventData.get<std::string>();
		return true;
}

bool EvtData_Set_Controlled_Actor::VBuildEventFromScript(void)
{
		//m_id = m_eventData.get<int>();
		return true;
}

void EvtData_ScriptEventTest_ToLua::VBuildEventData(void)
{
	//m_eventData.AssignNumber(EngineSubsystems::getInstance().m_pLuaStateManager->GetLuaState(), m_num);
}

bool EvtData_ScriptEventTest_FromLua::VBuildEventFromScript(void)
{
		//m_num = m_eventData.get<int>();
		return true;
}

void EvtData_Fire_Weapon::VBuildEventData(void)
{
	m_eventData.create_table_with(EngineSubsystems::getInstance().m_pLuaStateManager->GetLuaState(), "id", m_id, "roofus", 0);
}


void RegisterGameEvents(void)
{
	REGISTER_SCRIPT_EVENT(EvtData_Fire_Weapon, EvtData_Fire_Weapon::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_Gameplay_UI_Update, EvtData_Gameplay_UI_Update::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_Set_Controlled_Actor, EvtData_Set_Controlled_Actor::sk_EventType);

	REGISTER_SCRIPT_EVENT(EvtData_StartThrust, EvtData_StartThrust::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_EndThrust, EvtData_EndThrust::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_StartSteer, EvtData_StartSteer::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_EndSteer, EvtData_EndSteer::sk_EventType);

	// tests
	REGISTER_SCRIPT_EVENT(EvtData_ScriptEventTest_ToLua, EvtData_ScriptEventTest_ToLua::sk_EventType);
	REGISTER_SCRIPT_EVENT(EvtData_ScriptEventTest_FromLua, EvtData_ScriptEventTest_FromLua::sk_EventType);
}
