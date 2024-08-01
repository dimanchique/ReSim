cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(test
    LANGUAGES CXX
)

message("Configuring ReSim testing suite...")


# ------------------------ CONFIGURE GTEST UTILITY ------------------------

include(FetchContent)

# Fetching GoogleTest api from official GutHub repository
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# -------------------------------------------------------------------------


# Adding test modules separate
add_subdirectory(MOS6502)
add_subdirectory(I8080)

enable_testing()