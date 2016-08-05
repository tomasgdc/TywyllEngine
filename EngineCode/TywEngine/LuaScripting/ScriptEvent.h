#ifndef _LUA_SCRIPT_EVENT_H_
#define _LUA_SCRIPT_EVENT_H_

#include <TywEngine\EventManager\IEventManager.h>
#include <external\luasol2\sol.hpp>

class ScriptEvent;
typedef ScriptEvent* (*CreateEventForScriptFunctionType)(void);  // function ptr typedef to create a script event

//---------------------------------------------------------------------------------------------------------------------
// These macros implement exporting events to script.
//---------------------------------------------------------------------------------------------------------------------
#define REGISTER_SCRIPT_EVENT(eventClass, eventType) \
	ScriptEvent::RegisterEventTypeWithScript(#eventClass, eventType); \
	ScriptEvent::AddCreationFunction(eventType, &eventClass::CreateEventForScript)

#define EXPORT_FOR_SCRIPT_EVENT(eventClass) \
	public: \
		static ScriptEvent* CreateEventForScript(void) \
		{ \
			return new eventClass; \
		}


 //---------------------------------------------------------------------------------------------------------------------
// Script event base class.  This class is meant to be subclassed by any event that can be sent or received by the
// script.  Note that these events are not limited to script and can be received just fine by C++ listeners.
// Furthermore, since the Script data isn't built unless being received by a script listener, there's no worry about 
// performance.
//---------------------------------------------------------------------------------------------------------------------
class TYWENGINE_API ScriptEvent : public BaseEventData
{
	typedef std::map<EventType, CreateEventForScriptFunctionType> CreationFunctions;
	static CreationFunctions s_creationFunctions;

	bool m_eventDataIsValid;

protected:
	sol::state m_eventData;

public:
	// construction
	ScriptEvent(void) { m_eventDataIsValid = false; }

	// script event data, which should only be called from the appropriate ScriptExports functions
	sol::object GetEventData(void);  // called when event is sent from C++ to script
	bool SetEventData(sol::object eventData);  // called when event is sent from script to C++

	// Static helper functions for registering events with the script.  You should call the REGISTER_SCRIPT_EVENT(
	// macro instead of calling this function directly.  Any class that needs to be exported also needs to call the
	// EXPORT_FOR_SCRIPT_EVENT() inside the class declaration.
	static void RegisterEventTypeWithScript(const char* key, EventType type);
	static void AddCreationFunction(EventType type, CreateEventForScriptFunctionType pCreationFunctionPtr);
	static ScriptEvent* CreateEventFromScript(EventType type);

protected:
	// This function must be overridden if you want to fire this event from C++ and have it received by the script.
	// If you only fire the event from the script side, this function will never be called.  It's purpose is to 
	// fill in the m_eventData member, which is then passed to the script callback function in the listener.  This 
	// is only called the first time GetEventData() is called.  If the event is script-only, this function does not 
	// need to be overridden.
	virtual void VBuildEventData(void);

	// This function must be overridden if you want to fire this event from Script and have it received by C++.  If
	// you only fire this event from script and have it received by the script, it doesn't matter since m_eventData
	// will just be passed straight through.  Its purpose is to fill in any C++ member variables using the data in 
	// m_eventData (which is valid at the time of the call).  It is called when the event is fired from the script.
	// Return false if the data is invalid in some way, which will keep the event from actually firing.
	virtual bool VBuildEventFromScript(void) { return true; }
};

#endif
