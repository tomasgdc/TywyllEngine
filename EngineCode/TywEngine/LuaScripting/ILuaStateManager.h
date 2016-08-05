#ifndef _ENGINE_I_LUA_STATE_MANAGER_H_
#define _ENGINE_I_LUA_STATE_MANAGER_H_


class IScriptManager
{
public:
	virtual ~IScriptManager(void) {}
	virtual bool VInit(void) = 0;
	virtual void VExecuteFile(const char* resource) = 0;
	virtual void VExecuteString(const char* str) = 0;
};


#endif