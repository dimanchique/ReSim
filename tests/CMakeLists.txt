cmake_minimum_required(VERSION 3.16)
enable_testing()

include_directories(
        ../inc
        inc
)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/Operations/*.cpp)

set(
        CPU6502_TESTS
        "main_test.cpp"
        "CPU_Tests.cpp"
        "LDA_Tests.cpp"
        "LDX_Tests.cpp"
        "LDY_Tests.cpp"
        "JSR_Tests.cpp"
)


add_executable(
        main_tests
        ${CPU6502_TESTS}
        ${SRC_FILES}
)

target_link_libraries(
        main_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)
