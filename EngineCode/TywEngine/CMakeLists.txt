CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

PROJECT(TywEngine)



SET(HEADERS_EVENTMANAGER
	"EventManager/EventManagerImpl.h"
	"EventManager/Events.h"
	"EventManager/IEventManager.h"
)
SET(SOURCES_EVENTMANAGER
	"EventManager/EventManagerImpl.cpp"
	"EventManager/Events.cpp"
	"EventManager/IEventManager.cpp"
)
SOURCE_GROUP("EventManager\\Header Files" FILES ${HEADERS_EVENTMANAGER})
SOURCE_GROUP("EventManager\\Source Files" FILES ${SOURCES_EVENTMANAGER})


SET(HEADERS_FRAMEWORK
	"FrameWork/Engine.h"
	"FrameWork/EngineFactory.h"
	"FrameWork/EngineStrategies.h"
	"FrameWork/License.h"
	"FrameWork/EngineSubsystems.h"
)
SET(SOURCES_FRAMEWORK
	"FrameWork/Engine.cpp"
	"FrameWork/EngineFrame.cpp"
	"FrameWork/EnginePrintf.cpp"
	"FrameWork/EngineSubsystems.cpp"
)
SOURCE_GROUP("FrameWork\\Header Files" FILES ${HEADERS_FRAMEWORK})
SOURCE_GROUP("FrameWork\\Source Files" FILES ${SOURCES_FRAMEWORK})


SET(HEADERS_LUASCRIPTING
	"LuaScripting/ILuaStateManager.h"
	"LuaScripting/LuaStateManager.h"
	"LuaScripting/ScriptExporters.h"
	"LuaScripting/ScriptProcess.h"
	"LuaScripting/ScriptResource.h"
	"LuaScripting/ScriptEvent.h"
)
SET(SOURCES_LUASCRIPTING
	"LuaScripting/LuaStateManager.cpp"
	"LuaScripting/ScriptExporters.cpp"
	"LuaScripting/ScriptResource.cpp"
	"LuaScripting/ScriptProcess.cpp"
	"LuaScripting/ScriptEvent.cpp"
)
SOURCE_GROUP("LuaScripting\\Header Files" FILES ${HEADERS_LUASCRIPTING})
SOURCE_GROUP("LuaScripting\\Source Files" FILES ${SOURCES_LUASCRIPTING})


SET(HEADERS_MULTICORE
	"MultiCore/CriticalSection.h"
)
SET(SOURCES_MULTICORE
)
SOURCE_GROUP("MultiCore\\Header Files" FILES ${HEADERS_MULTICORE})
SOURCE_GROUP("MutliCore\\Source Files" FILES ${SOURCES_MULTICORE})


SET(HEADERS_NETWORK
)
SET(SOURCES_NETWORK
)
SOURCE_GROUP("Network\\Header Files" FILES ${HEADERS_NETWORK})
SOURCE_GROUP("Network\\Source Files" FILES ${SOURCES_NETWORK})


SET(HEADERS_SYSTEM
	"System/sys_public.h"
)
SET(SOURCES_SYSTEM
)
SOURCE_GROUP("System\\Header Files" FILES ${HEADERS_SYSTEM})
SOURCE_GROUP("System\\Source Files" FILES ${SOURCES_SYSTEM})


SET(HEADERS_SYSTEM_WIN32
	"System/win32/win_local.h"
)
SET(SOURCES_SYSTEM_WIN32
	"System/win32/win_cpu.cpp"
	"System/win32/win_main.cpp"
	"System/win32/win_wndproc.cpp"
)
SOURCE_GROUP("System\\Win32\\Header Files" FILES ${HEADERS_SYSTEM_WIN32})
SOURCE_GROUP("System\\Win32\\Source Files" FILES ${SOURCES_SYSTEM_WIN32})


SET(HEADERS_SYSTEM_LINUX
)
SET(SOURCES_SYSTEM_LINUX
)
SOURCE_GROUP("System\\Linux\\Header Files" FILES ${HEADERS_SYSTEM_LINUX})
SOURCE_GROUP("System\\Linux\\Source Files" FILES ${SOURCES_SYSTEM_LINUX})


ADD_LIBRARY(${PROJECT_NAME} SHARED
	${HEADERS_EVENTMANAGER}
	${SOURCES_EVENTMANAGER}
	${HEADERS_FRAMEWORK}
	${SOURCES_FRAMEWORK}
	${HEADERS_LUASCRIPTING}
	${SOURCES_LUASCRIPTING}
	${HEADERS_MULTICORE}
	${SOURCES_MULTICORE}
	${HEADERS_NETWORK}
	${SOURCES_NETWORK}
	${HEADERS_SYSTEM}
	${SOURCES_SYSTEM}
	${HEADERS_SYSTEM_LINUX}
	${SOURCES_SYSTEM_LINUX}
	${HEADERS_SYSTEM_WIN32}
	${SOURCES_SYSTEM_WIN32}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/glew32s.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/LUA.lib"
	${OPENGL_LIBRARIES}
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywLib_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywLib.lib"
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywRenderer_d.lib"
	optimized 	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywRenderer.lib"
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywGame_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywGame.lib"
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/EnginePch"
	"${CMAKE_SOURCE_DIR}/EngineCode"
	"${CMAKE_SOURCE_DIR}/External/LuaSol2"
	"${CMAKE_SOURCE_DIR}/External/Lua/src"
	"${CMAKE_SOURCE_DIR}/External/Glew/include"

)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_SOURCE_DIR}/EnginePch/stdafx.h"
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	)
cotire(${PROJECT_NAME})