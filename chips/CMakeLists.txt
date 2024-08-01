cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

message("Configuring chips...")
message("ReSim chips build type: ${RESIM_BUILD_TYPE}")

file(GLOB subdirs "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(chipdir ${subdirs})
    if(IS_DIRECTORY ${chipdir})
        get_filename_component(chipdir_name ${chipdir} NAME)
        message("found chipdir: ${chipdir_name}")
        add_subdirectory(${chipdir_name})
    endif()
endforeach()
