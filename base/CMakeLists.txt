cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
    base
    VERSION 0.1.0
    LANGUAGES CXX
)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/inc/base/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
add_library(ReSim::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ReSim::core
)