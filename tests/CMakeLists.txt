cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ../inc
        inc
)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/Operations/*.cpp)
file(GLOB CPU6502_TESTS ${PROJECT_SOURCE_DIR}/tests/*.cpp)

add_executable(
        main_tests
        ${CPU6502_TESTS}
        ${SOURCES}
)

target_link_libraries(
        main_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)
