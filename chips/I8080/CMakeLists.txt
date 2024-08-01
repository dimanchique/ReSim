cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
    i8080
    VERSION 1.0
    LANGUAGES CXX
)

file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/inc/I8080/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

if(NOT RESIM_BUILD_TYPE)
    set(RESIM_BUILD_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${RESIM_BUILD_TYPE} ${HEADERS} ${SOURCES})
add_library(ReSim::chip::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME}
    INTERFACE ReSim::core
    PUBLIC    ReSim::base
)