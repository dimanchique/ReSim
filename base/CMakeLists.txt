cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
    base
    VERSION 0.1.0
    LANGUAGES CXX
)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/inc/*.h)

add_library(${PROJECT_NAME} STATIC ${HEADERS})
add_library(ReSim::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ReSim::core
)
