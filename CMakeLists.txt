cmake_minimum_required(VERSION 3.26)
project(CPU_Emulator)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(CPU_Emulator main.cpp ${SRC_FILES})
