cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

message("Configuring MOS6502 tests...")
enable_testing()

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(mos6502-test ${HEADERS} ${SOURCES})

target_include_directories(mos6502-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(mos6502-test
    PRIVATE ReSim::chip::mos6502
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mos6502-test)

# Cross reference fullpath to original bin files
target_compile_definitions(mos6502-test PRIVATE TESTS_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/asm")