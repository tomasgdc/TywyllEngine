cmake_minimum_required(VERSION 3.4)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")


ADD_LIBRARY("LUA" STATIC ${SOURCES} ${HEADERS})