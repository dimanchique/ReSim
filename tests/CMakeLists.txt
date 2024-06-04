cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/inc/MOS6502
        ${PROJECT_SOURCE_DIR}/inc/I8080
        I8080/inc
        MOS6502/inc
)

file(GLOB SOURCES
        TestSuite_ReSim.cpp
        ${PROJECT_SOURCE_DIR}/src/MOS6502/*.cpp
        ${PROJECT_SOURCE_DIR}/src/MOS6502/Operations/*.cpp
        ${PROJECT_SOURCE_DIR}/src/I8080/*.cpp
        ${PROJECT_SOURCE_DIR}/src/I8080/Operations/*.cpp
)

file(GLOB RESIM_TESTS
        MOS6502/src/*.cpp
        I8080/src/*.cpp
)

add_executable(
        TestSuite_ReSim
        ${RESIM_TESTS}
        ${SOURCES}
)

target_link_libraries(
        TestSuite_ReSim
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestSuite_ReSim)

add_subdirectory(I8080)
add_subdirectory(MOS6502)

target_compile_definitions(TestSuite_ReSim PRIVATE TESTS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/tools/asm_tests/")
