cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/inc/MOS6502
        inc
)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/MOS6502/*.cpp ${PROJECT_SOURCE_DIR}/src/MOS6502/Operations/*.cpp)
file(GLOB MOS6502_TESTS ${PROJECT_SOURCE_DIR}/tests/MOS6502/*.cpp)

add_executable(
        main_tests
        ${MOS6502_TESTS}
        ${SOURCES}
)

target_link_libraries(
        main_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)

target_compile_definitions(main_tests PRIVATE TESTS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/tools/asm_tests/")