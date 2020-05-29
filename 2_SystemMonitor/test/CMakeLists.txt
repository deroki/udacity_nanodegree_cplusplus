cmake_minimum_required(VERSION 2.8)

project(test)
set(CMAKE_BUILD_TYPE Debug)
include_directories(../include)
set(SOURCES ../src/linux_parser.cpp
            parser.cpp
            ../src/processor.cpp
            ../src/system.cpp
            ../src/process.cpp)
#file(GLOB SOURCES ../src/*.cpp)
add_executable(test ${SOURCES})