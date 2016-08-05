cmake_minimum_required(VERSION 3.4)


file(GLOB HEADERS "*.h")
SOURCE_GROUP("Sol\\Compatibility\\Header Files" FILES ${HEADERS})

file(GLOB HEADERS_HPP "*.hpp")
SOURCE_GROUP("Sol\\Compatibility\\Header Files" FILES ${HEADERS_HPP})

file(GLOB HEADERS_INL "*.inl")
SOURCE_GROUP("Sol\\Compatibility\\Headers Files" FILES ${HEADERS_INL})
