#ifndef _ENGINE_SCRIPT_PROCESS_H_
#define _ENGINE_SCRIPT_PROCESS_H_

#include "LuaStateManager.h"


//---------------------------------------------------------------------------------------------------------------------
// ScriptProcess                                                  Inherit process
//---------------------------------------------------------------------------------------------------------------------
class TYWENGINE_API ScriptProcess
{
	unsigned long m_frequency, m_time;
	sol::object m_scriptInitFunction, m_scriptUpdateFunction;
	sol::object m_scriptSuccessFunction, m_scriptFailFunction, m_scriptAbortFunction;
	sol::object m_self;

public:
	static void RegisterScriptClass(void);

protected:
	// Process interface
	virtual void VOnInit(void);
	virtual void VOnUpdate(unsigned long deltaMs);
	virtual void VOnSuccess(void);
	virtual void VOnFail(void);
	virtual void VOnAbort(void);

private:
	// private helpers
	static void RegisterScriptClassFunctions(sol::object& metaTableObj);
	static sol::object CreateFromScript(sol::object self, sol::object constructionData, sol::object originalSubClass);
	virtual bool BuildCppDataFromScript(sol::object scriptClass, sol::object constructionData);

	// These are needed because the base-class version of these functions are all const and LuaPlus can't deal
	// with registering const functions.
	//bool ScriptIsAlive(void) { return IsAlive(); }
	//bool ScriptIsDead(void) { return IsDead(); }
	//bool ScriptIsPaused(void) { return IsPaused(); }

	// This wrapper function is needed so we can translate a Lua script object to something C++ can use.
	void ScriptAttachChild(sol::object child);

	// don't allow construction outside of this class
	explicit ScriptProcess(void);
};


#endif