#include "../../External/LuaSol2/sol.hpp"
#include "ILuaStateManager.h"

//---------------------------------------------------------------------------------------------------------------------
// LuaStateManager                              - Chapter 12, page 367
//---------------------------------------------------------------------------------------------------------------------
class TYWENGINE_API LuaStateManager : public IScriptManager
{
	sol::state  m_luaState;
	std::string m_lastError;
public:
	LuaStateManager(void);
	virtual ~LuaStateManager(void);

	// IScriptManager interface
	virtual bool VInit(void) override;
	virtual void VExecuteFile(const char* resource) override;
	virtual void VExecuteString(const char* str) override;

	sol::object GetGlobalVars(void);
	sol::state* GetLuaState(void);

	// public helpers
	sol::object CreatePath(const char* pathString, bool toIgnoreLastElement = false);
	void ConvertVec3ToTable(const glx::vec3<float>& vec, sol::object& outLuaTable) const;
	void ConvertTableToVec3(const sol::object& luaTable, glx::vec3<float>& outVec3) const;

private:
	void SetError(int errorNum);
	void ClearStack(void);
};