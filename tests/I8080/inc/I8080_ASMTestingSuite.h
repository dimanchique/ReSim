#pragma once
#include <filesystem>
#include "I8080_TestingSuite.h"

class I8080_ASMTestFixture : public I8080_TestFixture {
public:
    void SetExecutable(const std::string& filepath){
        std::filesystem::path projectRoot = TESTS_SOURCE_DIR;
        std::filesystem::path filePath = projectRoot / filepath;
        const bool loadSuccess = cpu.LoadROM(filePath.generic_string().c_str(), mem);
        ASSERT_TRUE(loadSuccess);
    }

    void RunTest() {
        cyclesPassed = cpu.Run();
    }
};
