cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
    applications
    VERSION 0.1.0
    LANGUAGES CXX
)

add_subdirectory(MOS6502)
add_subdirectory(I8080)

add_custom_target(all-applications)
add_dependencies(all-applications
    6502-applications
    8080-applications
)
