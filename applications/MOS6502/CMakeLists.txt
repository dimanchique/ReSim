cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

add_subdirectory(Wozmon)
add_subdirectory(eh-basic)

add_custom_target(6502-applications)
add_dependencies(6502-applications
    6502-wozmon
    6502-eh-basic
)
