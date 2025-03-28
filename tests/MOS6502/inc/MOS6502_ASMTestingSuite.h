#pragma once
#include <filesystem>
#include "MOS6502_TestingSuite.h"

class MOS6502_ASMTestFixture : public MOS6502_TestFixture {
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
