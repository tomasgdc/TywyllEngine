CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

PROJECT(TywPhysics)

SET(HEADERS
	"Physics.h"
	"PhysicsDebugDrawer.h"
	"PhysicsEventListener.h"
)
SET(SOURCES
	"Physics.cpp"
	"PhysicsDebugDrawer.cpp"
	"PhysicsEventListener.cpp"
)
SOURCE_GROUP("Header Files" FILES ${HEADERS})
SOURCE_GROUP("Source Files" FILES ${SOURCES})


ADD_LIBRARY(${PROJECT_NAME} SHARED
	${HEADERS}
	${SOURCES}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywLib_d.lib"
	optimized 	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywLib.lib"
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywRenderer_d.lib"
	optimized 	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywRenderer.lib"
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywEngine_d.lib"
	optimized 	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywEngine.lib"
	)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	"${CMAKE_SOURCE_DIR}/EnginePch"
	"${CMAKE_CURRENT_SOURCE_DIR}/../"
 )
 
set_target_properties(${PROJECT_NAME} PROPERTIES 
	COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_SOURCE_DIR}/EnginePch/stdafx.h"
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	)
cotire(${PROJECT_NAME})