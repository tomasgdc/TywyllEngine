CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

PROJECT(TywGame)
	
SET(HEADERS_ACTORS
	"Actors/RenderComponentInterface.h"
	"Actors/Actor.h"
	"Actors/ActorFactory.h"
	"Actors/Actors.h"
	"Actors/ActorComponent.h"
	"Actors/AudioComponent.h"
	"Actors/PhysicsComponent.h"
	"Actors/RenderingComponent.h"
	"Actors/TransformComponent.h"
)
SET(SOURCES_ACTORS
	"Actors/Actor.cpp"
	"Actors/ActorFactory.cpp"
	"Actors/Actors.cpp"
	"Actors/ActorComponent.cpp"
	"Actors/AudioComponent.cpp"
	"Actors/PhysicsComponent.cpp"
	"Actors/RenderingComponent.cpp"
	"Actors/TransformComponent.cpp"
)
SOURCE_GROUP("Actors\\Header Files" FILES ${HEADERS_ACTORS})
SOURCE_GROUP("Actors\\Source Files" FILES ${SOURCES_ACTORS})


SET(HEADERS_AI
	"AI/Pathing.h"
)
SET(SOURCES_AI
	"AI/Pathing.cpp"
)
SOURCE_GROUP("AI\\Header Files" FILES ${HEADERS_AI})
SOURCE_GROUP("AI\\Source Files" FILES ${SOURCES_AI})


SET(HEADERS
	"Game.h"
	"BaseGameLogic.h"
	"IGameLogic.h"
	"GameLogic.h"
	"GameOptions.h"
	"HumanView.h"
	"IScreenElement.h"
	"ScreenElementScene.h"
	"AIPlayerView.h"
	"MainView.h"
	"GameEvents.h"
)
SET(SOURCES
	"Game.cpp"
	"BaseGameLogic.cpp"
	"GameLogic.cpp"
	"HumanView.cpp"
	"AIPlayerView.cpp"
	"MainView.cpp"
	"GameEvents.cpp"
)
SOURCE_GROUP("Header Files" FILES ${HEADERS})
SOURCE_GROUP("Source Files" FILES ${SOURCES})



ADD_LIBRARY(${PROJECT_NAME} SHARED
	${HEADERS_ACTORS}
	${SOURCES_ACTORS}
	${HEADERS_AI}
	${SOURCES_AI}
	${HEADERS}
	${SOURCES}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/zlibstat.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/LUA.lib"
	debug	 "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/tinyxml2_d.lib"
	optimized "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/tinyxml2.lib"
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywLib_d.lib"
	optimized 	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywLib.lib"
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywAnimation_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywAnimation.lib"
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywRenderer_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywRenderer.lib"
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywEngine_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywEngine.lib"
	debug		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywPhysics_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywPhysics.lib"
	)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/EngineCode"
	"${CMAKE_SOURCE_DIR}/EnginePch"
	"${CMAKE_SOURCE_DIR}/external/tinyxml2"
	"${CMAKE_SOURCE_DIR}/External/LuaSol2"
	"${CMAKE_SOURCE_DIR}/External/Lua/src"
 )
 
set_target_properties(${PROJECT_NAME} PROPERTIES 
	COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_SOURCE_DIR}/EnginePch/stdafx.h"
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	)
cotire(${PROJECT_NAME})