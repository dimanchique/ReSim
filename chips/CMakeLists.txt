cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

message(STATUS "Configuring chips...")
message(STATUS "ReSim chips build type: ${RESIM_BUILD_TYPE}")

file(GLOB subdirs "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(chipdir ${subdirs})
    if(IS_DIRECTORY ${chipdir})
        get_filename_component(chipdir_name ${chipdir} NAME)
        message(STATUS "found chipdir: ${chipdir_name}")
        if(EXISTS "${chipdir}/CMakeLists.txt")
            add_subdirectory(${chipdir_name})
        else ()
            message(WARNING "${chipdir_name} found but doesn't contain CMakeLists.txt")
        endif()
    endif()
endforeach()
