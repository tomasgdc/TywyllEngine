#include <stdafx.h>
#include "../TywLib/math/GLXVec3.h"
#include "LuaStateManager.h"


LuaStateManager::LuaStateManager(void)
{
}

LuaStateManager::~LuaStateManager(void)
{

}

bool LuaStateManager::VInit(void)
{
	//Open common libraries
	m_luaState.open_libraries(sol::lib::base, sol::lib::package);

	//register functions
	m_luaState.set_function("ExecuteFile", &LuaStateManager::VExecuteFile);
	m_luaState.set_function("ExecuteString", &LuaStateManager::VExecuteString);
	return true;
}

void LuaStateManager::VExecuteFile(const char* path)
{
	//TOOD: Check if was parsed
	m_luaState.script_file(path);
}

void LuaStateManager::VExecuteString(const char* chunk)
{
	// Most strings are passed straight through to the Lua interpreter
	if (strlen(chunk) <= 1 || chunk[0] != '=')
	{
		//TODO: catch error
		m_luaState.script_file(chunk);
	}

	// If the string starts with '=', wrap the statement in the print() function.
	else
	{
		//TODO: catch error
		std::string buffer("print(");
		buffer += (chunk + 1);
		buffer += ")";
		m_luaState.script_file(buffer.c_str());	
	}
}

void LuaStateManager::SetError(int errorNum)
{
	// Note: If we get an error, we're hosed because LuaPlus throws an exception.  So if this function
	// is called and the error at the bottom triggers, you might as well pack it in.

	/*
	LuaPlus::LuaStackObject stackObj(m_pLuaState, -1);
	const char* errStr = stackObj.GetString();
	if (errStr)
	{
		m_lastError = errStr;
		ClearStack();
	}
	else
		m_lastError = "Unknown Lua parse error";

	GCC_ERROR(m_lastError);
	*/
}

void LuaStateManager::ClearStack(void)
{
	//m_luaState.release();
}

/*
sol::object LuaStateManager::GetGlobalVars(void)
{
	retu;
}
*/

sol::state* LuaStateManager::GetLuaState(void)
{
	return &m_luaState;
}

/*
sol::object LuaStateManager::CreatePath(const char* pathString, bool toIgnoreLastElement)
{
	StringVec splitPath;
	Split(pathString, splitPath, '.');
	if (toIgnoreLastElement)
		splitPath.pop_back();

	LuaPlus::LuaObject context = GetGlobalVars();
	for (auto it = splitPath.begin(); it != splitPath.end(); ++it)
	{
		// make sure we still have a valid context
		if (context.IsNil())
		{
			GCC_ERROR("Something broke in CreatePath(); bailing out (element == " + (*it) + ")");
			return context;  // this will be nil
		}

		// grab whatever exists for this element
		const std::string& element = (*it);
		LuaPlus::LuaObject curr = context.GetByName(element.c_str());

		if (!curr.IsTable())
		{
			// if the element is not a table and not nil, we clobber it
			if (!curr.IsNil())
			{
				GCC_WARNING("Overwriting element '" + element + "' in table");
				context.SetNil(element.c_str());
			}

			// element is either nil or was clobbered so add the new table
			context.CreateTable(element.c_str());
		}

		context = context.GetByName(element.c_str());
	}

	// if we get here, we have created the path
	return context;
}
*/


void LuaStateManager::ConvertVec3ToTable(const glx::vec3<float>& vec, sol::object& outLuaTable) const
{
	/*
	outLuaTable.AssignNewTable(GetLuaState());
	outLuaTable.SetNumber("x", vec.x);
	outLuaTable.SetNumber("y", vec.y);
	outLuaTable.SetNumber("z", vec.z);
	*/
}


void LuaStateManager::ConvertTableToVec3(const sol::object& luaTable, glx::vec3<float>& outVec3) const
{
	/*
	LuaPlus::LuaObject temp;

	// x
	temp = luaTable.Get("x");
	if (temp.IsNumber())
		outVec3.x = temp.GetFloat();
	else
		GCC_ERROR("luaTable.x is not a number");

	// y
	temp = luaTable.Get("y");
	if (temp.IsNumber())
		outVec3.y = temp.GetFloat();
	else
		GCC_ERROR("luaTable.y is not a number");

	// z
	temp = luaTable.Get("z");
	if (temp.IsNumber())
		outVec3.z = temp.GetFloat();
	else
		GCC_ERROR("luaTable.z is not a number");
		*/
}