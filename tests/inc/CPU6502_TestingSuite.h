#pragma once

#include <gtest/gtest.h>
#include "CPU6502_OpCodes.h"
#include "CPU6502.h"
#include "Memory.h"

class CPU6502_TestFixture : public testing::Test{
public:
    Memory mem{64};
    CPU6502 cpu{};

    S32 CyclesPassed;
    S32 CyclesExpected;

    void SetUp() override{
        cpu.Reset(mem);
    }

    void TearDown() override{
        std::printf("Test finished. Cycles passed/expected: %d/%d", CyclesPassed, CyclesExpected);
    }

    void CheckCyclesCount(S32 CustomCyclesExpected = -1) const {
        if (CustomCyclesExpected == -1)
            EXPECT_EQ(CyclesPassed, CyclesExpected);
        else
            EXPECT_EQ(CyclesPassed, CustomCyclesExpected);
    }
};
