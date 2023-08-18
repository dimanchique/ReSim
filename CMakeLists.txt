cmake_minimum_required(VERSION 3.26)
project(CPU_Emulator)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc)

file(
        GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Operations/*.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
add_executable(CPU_Emulator main.cpp ${SRC_FILES})
