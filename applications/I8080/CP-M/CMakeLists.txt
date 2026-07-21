cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
        8080-cpm
        VERSION 0.1.0
        LANGUAGES CXX
)

add_executable(8080-cpm main.cpp cli_parser.h image_manager.h keyboard.h tty.h)
target_link_libraries(8080-cpm PRIVATE ReSim::chip::i8080)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src")
add_custom_command(
        TARGET 8080-cpm POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
        "${CMAKE_CURRENT_BINARY_DIR}/src/"
)
target_compile_definitions(8080-cpm PRIVATE SOURCE_DIR="${CMAKE_CURRENT_BINARY_DIR}/src")
