#pragma once
#include <gtest/gtest.h>
#include "MOS6502/MOS6502_OpCodes.h"
#include "MOS6502/MOS6502.h"
#include "memory.h"

#include "chrono"
#include "MOS6502_TestingSuite.h"

class MOS6502_ASMTestFixture : public MOS6502_TestFixture {
public:
    std::chrono::steady_clock::time_point begin, end;
    double duration;

    void SetExecutable(const std::string &path, Memory &memory){
        const bool loadSuccess = cpu.LoadROM(path.c_str(), memory);
        ASSERT_TRUE(loadSuccess);
    }

    void RunTest() {
        begin = std::chrono::steady_clock::now();
        cyclesPassed = cpu.Run();
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }

    void TearDown() override {
        std::cout << "Execution duration: " << duration / 1e6 << "[s]" << std::endl;
        std::cout << "Cycles count: " << cyclesPassed  << std::endl;
        std::cout << "Cycles/s: " << cyclesPassed / (duration / 1e6)  << std::endl;
        std::cout << "Frequency: " << cyclesPassed / duration << " MHz" << std::endl;
    }
};
