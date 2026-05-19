cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
        6502-wozmon
        VERSION 0.1.0
        LANGUAGES CXX
)

add_executable(6502-wozmon main.cpp keyboard.h tty.h)
target_link_libraries(6502-wozmon PRIVATE ReSim::chip::mos6502)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src")
add_custom_command(
        TARGET 6502-wozmon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
        "${CMAKE_CURRENT_BINARY_DIR}/src/"
)
target_compile_definitions(6502-wozmon PRIVATE SOURCE_DIR="${CMAKE_CURRENT_BINARY_DIR}/src")
