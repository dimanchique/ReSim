cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/inc/I8080
        inc
)

file(GLOB SOURCES
        TestSuite_I8080.cpp
        ${PROJECT_SOURCE_DIR}/src/I8080/*.cpp
        ${PROJECT_SOURCE_DIR}/src/I8080/Operations/*.cpp)
file(GLOB I8080_TESTS
        src/*.cpp)

add_executable(
        TestSuite_I8080
        ${I8080_TESTS}
        ${SOURCES}
)

target_link_libraries(
        TestSuite_I8080
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestSuite_I8080)

target_compile_definitions(TestSuite_I8080 PRIVATE TESTS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/tools/asm_tests/")