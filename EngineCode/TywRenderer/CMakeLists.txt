CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

PROJECT(TywRenderer)


SET(HEADERS_OPENGL
	"OpenGL/BufferObject.h"
	"OpenGL/Texture2D.h"
)
SET(SOURCES_OPENGL
	"OpenGL/BufferObject.cpp"
	"OpenGL/Texture2D.cpp"
)
SOURCE_GROUP("OpenGL\\Header Files" FILES ${HEADERS_OPENGL})
SOURCE_GROUP("OpenGL\\Source Files" FILES ${SOURCES_OPENGL})




SET(HEADERS_THIRDPARTY_FREETYPE
	"ThirdParty/FreeType/FreetypeLoad.h"
)
SET(SOURCES_THIRDPARTY_FREETYPE
	"ThirdParty/FreeType/FreetypeLoad.cpp"
)
SOURCE_GROUP("ThirdParty\\FreeType\\Header Files" FILES ${HEADERS_THIRDPARTY_FREETYPE})
SOURCE_GROUP("ThirdParty\\FreeType\\Source Files" FILES ${SOURCES_THIRDPARTY_FREETYPE})


SET(HEADERS_THIRDPARTY_IMGUI
	"ThirdParty/ImGui/imconfig.h"
	"ThirdParty/ImGui/imgui.h"
	"ThirdParty/ImGui/imgui_internal.h"
	"ThirdParty/ImGui/stb_rect_pack.h"
	"ThirdParty/ImGui/stb_textedit.h"
	"ThirdParty/ImGui/stb_truetype.h"

)
SET(SOURCES_THIRDPARTY_IMGUI
	"ThirdParty/ImGui/imgui.cpp"
	"ThirdParty/ImGui/imgui_demo.cpp"
	"ThirdParty/ImGui/imgui_draw.cpp"
)
SOURCE_GROUP("ThirdParty\\ImGui\\Header Files" FILES ${HEADERS_THIRDPARTY_IMGUI})
SOURCE_GROUP("ThirdParty\\ImGui\\Source Files" FILES ${SOURCES_THIRDPARTY_IMGUI})


SET(HEADERS
	"Font.h"
	"Image.h"
	"Material.h"
	"Model.h"
	"Model_local.h"
	"Model_obj.h"
	"ModelManager.h"
	"RenderLog.h"
	"RenderProgs.h"
	"RenderWorld.h"
	"VertexCache.h"
	"ISceneNode.h"
	"SceneNode.h"
	"IRenderer.h"
	"IRenderState.h"
	"GLRenderer.h"
	"IRendererInitializer.h"
	"WindowsGLRendererInitializer.h"
	"Lights.h"
	"RayCast.h"
	"SceneManager.h"
	
)
SET(SOURCES
	"Font.cpp"
	"ImageManager.cpp"
	"Material.cpp"
	"Model.cpp"
	"Model_md5.cpp"
	"Model_obj.cpp"
	"Model_sprite.cpp"
	"ModelManager.cpp"
	"RenderLog.cpp"
	"RenderProgs.cpp"
	"RenderProgs_GLSL.cpp"
	"RenderSystem_draw.cpp"
	"RenderWorld.cpp"
	"tri_trisurf.cpp"
	"VertexCache.cpp"
	"SceneNode.cpp"
	"SceneManager.cpp"
	"RayCast.cpp"
	"Model_frustrum.cpp"
	"Model_plane.cpp"
	"Lights.cpp"
	"GLRenderer.cpp"
	"GLRendererGUI.cpp"
	"WindowsGLRendererInitializer.cpp"
	"IRendererInitializer.cpp"

)
SOURCE_GROUP("Header Files" FILES ${HEADERS})
SOURCE_GROUP("Source Files" FILES ${SOURCES})

	
ADD_LIBRARY(${PROJECT_NAME} SHARED
	${HEADERS_OPENGL}
	${SOURCES_OPENGL}
	${HEADERS_THIRDPARTY_FREETYPE}
	${SOURCES_THIRDPARTY_FREETYPE}
	${HEADERS_THIRDPARTY_IMGUI}
	${SOURCES_THIRDPARTY_IMGUI}
	${HEADERS}
	${SOURCES}
)

	
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/glew32s.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/freetypeMT.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/soil2.lib"
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/glew32s.lib"
	${OPENGL_LIBRARIES}
	debug 		"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug/TywLib_d.lib"
	optimized	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Release/TywLib.lib"
	)



TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	"${CMAKE_CURRENT_SOURCE_DIR}/../"
	"${CMAKE_SOURCE_DIR}/External/Soil2/src"
	"${CMAKE_SOURCE_DIR}/External/FreeType/include"
	"${CMAKE_SOURCE_DIR}/External/Glew/include"
	"${CMAKE_SOURCE_DIR}/EnginePch"
	)

	
set_target_properties(${PROJECT_NAME} PROPERTIES 
	COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_SOURCE_DIR}/EnginePch/stdafx.h"
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	)
cotire(${PROJECT_NAME})