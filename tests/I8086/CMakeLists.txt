cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

message("Configuring I8086 tests...")
enable_testing()

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(i8086-test ${HEADERS} ${SOURCES})

target_include_directories(i8086-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(i8086-test
    PRIVATE ReSim::chip::i8086
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(i8086-test)

# Cross reference fullpath to original bin files
target_compile_definitions(i8086-test PRIVATE TESTS_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/asm")