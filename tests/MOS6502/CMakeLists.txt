cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/inc/MOS6502
        inc
)

file(GLOB SOURCES
        #TestSuite_MOS6502.cpp
        ${PROJECT_SOURCE_DIR}/src/MOS6502/*.cpp
        ${PROJECT_SOURCE_DIR}/src/MOS6502/Operations/*.cpp)
file(GLOB MOS6502_TESTS
        src/*.cpp)

add_executable(
        TestSuite_MOS6502
        ${MOS6502_TESTS}
        ${SOURCES}
)

target_link_libraries(
        TestSuite_MOS6502
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestSuite_MOS6502)

target_compile_definitions(TestSuite_MOS6502 PRIVATE TESTS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/tools/asm_tests/")