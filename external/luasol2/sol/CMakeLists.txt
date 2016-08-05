cmake_minimum_required(VERSION 3.4)

file(GLOB HEADERS_HPP "*.hpp")
SOURCE_GROUP("Sol\\Header Files" FILES ${HEADERS_HPP})

ADD_SUBDIRECTORY(compatibility)