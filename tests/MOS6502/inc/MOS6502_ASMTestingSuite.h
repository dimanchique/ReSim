#pragma once
#include <gtest/gtest.h>
#include "MOS6502_OpCodes.h"
#include "MOS6502.h"
#include "Memory.h"

#ifdef TEST_EXECUTION_PERFORMANCE
#include "chrono"
#endif

class MOS6502_ASMTestFixture : public testing::Test {
public:
    MOS6502 cpu{};
    Memory mem{64};

    U32 cyclesPassed = 0;

#ifdef TEST_EXECUTION_PERFORMANCE
    std::chrono::steady_clock::time_point begin, end;
    double duration;
#endif

    void SetUp() override {
        cpu.Reset(mem, 0xFFFC);
    }

    void SetExecutable(const std::string &path, Memory &memory, const WORD startingAddress){
        const bool loadSuccess = cpu.LoadROM(path.c_str(), memory, startingAddress);
        ASSERT_TRUE(loadSuccess);
    }

    void RunTest() {
#ifdef TEST_EXECUTION_PERFORMANCE
        begin = std::chrono::steady_clock::now();
#endif
        cyclesPassed = cpu.Run(mem);
#ifdef TEST_EXECUTION_PERFORMANCE
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
#endif
    }

    void TearDown() override {
#ifdef TEST_EXECUTION_PERFORMANCE
        std::cout << "Execution duration: " << duration / 1e6 << "[s]" << std::endl;
        std::cout << "Cycles count: " << cyclesPassed  << std::endl;
        std::cout << "Cycles/s: " << cyclesPassed / (duration / 1e6)  << std::endl;
        std::cout << "Frequency: " << cyclesPassed / duration << " MHz" << std::endl;
#endif
    }
};
