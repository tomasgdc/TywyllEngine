#-------------------------------------------------------------------
# This file is part of the CMake build system for TywyllEngine
#     (Object-oriented Graphics Rendering Engine)
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-----------------------------------------------------------------


######################################################################
# TYWLL ENGINE BUILD SYSTEM
# Welcome to the CMake build system for TywyllEngine.
# This is the main file where we prepare the general build environment
# and provide build configuration options.
######################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(TywyllEngine)


find_package(OpenGL REQUIRED)

# Reduce the config types to only Debug and Release
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --my-debug-flags")
SET(CMAKE_DEBUG_POSTFIX "_d")


IF(WIN32)
  ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ENDIF()

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)


INCLUDE(cotire)


ADD_SUBDIRECTORY(EngineCode/Application)
ADD_SUBDIRECTORY(EngineCode/TywAnimation)
ADD_SUBDIRECTORY(EngineCode/TywEngine)
ADD_SUBDIRECTORY(EngineCode/TywGame)
ADD_SUBDIRECTORY(EngineCode/TywLib)
ADD_SUBDIRECTORY(EngineCode/TywRenderer)
ADD_SUBDIRECTORY(EngineCode/TywPhysics)


MESSAGE("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
if(CMAKE_CONFIGURATION_TYPES)
    MESSAGE("Multi-configuration generator")
else()
    MESSAGE("Single-configuration generator")
endif()