cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
    core
    VERSION 0.1.0
    LANGUAGES CXX
)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/inc/core/*.h)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})
add_library(ReSim::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/inc)
