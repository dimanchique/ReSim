cmake_minimum_required(VERSION 3.26)
enable_testing()

include_directories(inc)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/Operations/*.cpp)

set(
        CPU6502_SOURCES
        "main_test.cpp"
        "test.cpp"
        )

add_executable(
        main_tests
        ${CPU6502_SOURCES}
        ${SRC_FILES}
)

target_link_libraries(
        main_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)
