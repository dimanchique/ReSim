#pragma once
#include <gtest/gtest.h>
#include "MOS6502/MOS6502_OpCodes.h"
#include "MOS6502/MOS6502.h"
#include "base/memory.h"

class MOS6502_TestFixture : public testing::Test {
public:
    Memory mem{64};
    MOS6502 cpu{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    void SetUp() override {
        cpu.Reset(mem);
    }

    void TearDown() override {
        std::printf("Cycles passed %d expected %d\n", cyclesPassed, cyclesExpected);
    }

    void CheckCyclesCount(S32 customCyclesExpected = -1) const noexcept {
        if (customCyclesExpected == -1)
            EXPECT_EQ(cyclesPassed, cyclesExpected);
        else
            EXPECT_EQ(cyclesPassed, customCyclesExpected);
    }
};
