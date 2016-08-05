CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

PROJECT(TywLib)

SET(HEADERS_FILE
	"file/FileDevice.h"
	"file/FileSystem.h"
	"file/DiskFileDevice.h"
)
SET(SOURCES_FILE
	"file/DiskFileDevice.cpp"
	"file/FileSystem.cpp"
)
SOURCE_GROUP("File\\Header Files" FILES ${HEADERS_FILE})
SOURCE_GROUP("File\\Source Files" FILES ${SOURCES_FILE})

SET(HEADERS_MATH
	"math/GLXConstants.h"
	"math/GLXMat4x4.h"
	"math/GLXMat4x4.inl"
	"math/GLXMath.h"
	"math/GLXMath.inl"
	"math/GLXQuat.h"
	"math/GLXQuat.inl"
	"math/GLXVec2.h"
	"math/GLXVec2.inl"
	"math/GLXVec3.h"
	"math/GLXVec3.inl"
	"math/GLXVec4.h"
	"math/GLXVec4.inl"
)
SET(SOURCES_MATH
	"math/GLXMath_impl.cpp"
)
SOURCE_GROUP("Math\\Header Files" FILES ${HEADERS_MATH})
SOURCE_GROUP("Math\\Source Files" FILES ${SOURCES_MATH})


SET(HEADERS_GEOMETRY
	"geometry/JointTransform.h"
	"geometry/VertData.h"
)
SET(SOURCES_GEOMETRY
	"geometry/JointTransform.cpp"
)
SOURCE_GROUP("Geometry\\Header Files" FILES ${HEADERS_GEOMETRY})
SOURCE_GROUP("Geometry\\Source Files" FILES ${SOURCES_GEOMETRY})



SET(HEADERS_MEMORY
	"memory/Heap.h"
)
SET(SOURCES_MEMORY
)
SOURCE_GROUP("Memory\\Header Files" FILES ${HEADERS_MEMORY})
SOURCE_GROUP("Memory\\Source Files" FILES ${SOURCES_MEMORY})


SET(HEADERS_TEXT
	"text/Lexer.h"
	"text/Parser.h"
	"text/Token.h"
	
)
SET(SOURCES_TEXT
	"text/Lexer.cpp"
	"text/Parser.cpp"
	"text/Token.cpp"
)
SOURCE_GROUP("Text\\Header Files" FILES ${HEADERS_TEXT})
SOURCE_GROUP("Text\\Source Files" FILES ${SOURCES_TEXT})



SET(HEADERS_UTILITIES
	"utilities/templates.h"
	"utilities/EngineString.h"
)
SET(SOURCES_UTILITIES
	"utilities/EngineString.cpp"
)
SOURCE_GROUP("Utilities\\Header Files" FILES ${HEADERS_UTILITIES})
SOURCE_GROUP("Utilities\\Source Files" FILES ${SOURCES_UTILITIES})


SET(HEADERS_RESOURCE_CACHE
	"ResourceCache/IResourceFile.h"
	"ResourceCache/IResourceLoader.h"
	"ResourceCache/ResCache.h"
	"ResourceCache/XmlResource.h"
	"ResourceCache/ZipFile.h"
)
SET(SOURCES_RESOURCE_CACHE
	"ResourceCache/ResCache.cpp"
	"ResourceCache/XmlResource.cpp"
	"ResourceCache/ZipFile.cpp"
)
SOURCE_GROUP("ResourceCache\\Header Files" FILES ${HEADERS_RESOURCE_CACHE})
SOURCE_GROUP("ResourceCache\\Source Files" FILES ${SOURCES_RESOURCE_CACHE})

ADD_LIBRARY(${PROJECT_NAME} STATIC
	${HEADERS_FILE}
	${SOURCES_FILE}
	${HEADERS_MATH}
	${SOURCES_MATH}
	${HEADERS_GEOMETRY}
	${SOURCES_GEOMETRY}
	${HEADERS_MEMORY}
	${SOURCES_MEMORY}
	${HEADERS_TEXT}
	${SOURCES_TEXT}
	${HEADERS_UTILITIES}
	${SOURCES_UTILITIES}
	${HEADERS_RESOURCE_CACHE}
	${SOURCES_RESOURCE_CACHE}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	debug	 "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/tinyxml2_d.lib"
	optimized "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/tinyxml2.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/zlibstat.lib"
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
	 ${CMAKE_CURRENT_SOURCE_DIR}
	"${CMAKE_SOURCE_DIR}/EnginePch"
	"${CMAKE_SOURCE_DIR}/external/zlib-1.2.8"
	"${CMAKE_SOURCE_DIR}/external/tinyxml2"
	)
	
set_target_properties(${PROJECT_NAME} PROPERTIES 
	COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_SOURCE_DIR}/EnginePch/stdafx.h"
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	)
cotire(${PROJECT_NAME})