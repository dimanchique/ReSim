cmake_minimum_required(VERSION 3.22)

project(
    ReSim
    VERSION 0.1.0
    LANGUAGES CXX
)

if(RESIM_BUILD_SHARED)
    set(RESIM_BUILD_TYPE SHARED)
else()
    set(RESIM_BUILD_TYPE STATIC)
endif()

add_subdirectory(core)
add_subdirectory(base)
add_subdirectory(chips)

if(RESIM_BUILD_TESTING)
    add_subdirectory(tests)
    
    # Enable CTest testing suit at global point
    enable_testing()
endif()

# special main target for experimenting
add_executable(ReSim main.cpp)
target_link_libraries(ReSim
    PRIVATE ReSim::core
    PRIVATE ReSim::base
    PRIVATE ReSim::chip::mos6502
    PRIVATE ReSim::chip::i8080
)
