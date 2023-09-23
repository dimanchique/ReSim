#pragma once

#include <gtest/gtest.h>
#include "CPU6502_OpCodes.h"
#include "CPU6502.h"
#include "Memory.h"

class CPU6502_TestFixture : public testing::Test{
public:
    Memory mem{64};
    CPU6502 cpu{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    void SetUp() override{
        cpu.Reset(mem);
    }

    void TearDown() override{
        std::printf("Test finished. cycles passed/expected: %d/%d\n", cyclesPassed, cyclesExpected);
    }

    void CheckCyclesCount(S32 customCyclesExpected = -1) const {
        if (customCyclesExpected == -1)
            EXPECT_EQ(cyclesPassed, cyclesExpected);
        else
            EXPECT_EQ(cyclesPassed, customCyclesExpected);
    }
};
