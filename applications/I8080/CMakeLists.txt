cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

add_subdirectory(CP-M)

add_custom_target(8080-applications)
add_dependencies(8080-applications
    8080-cpm
)
