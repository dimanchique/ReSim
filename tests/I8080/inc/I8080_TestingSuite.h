#pragma once
#include <gtest/gtest.h>
#include "I8080_OpCodes.h"
#include "I8080.h"
#include "Memory.h"

class I8080_TestFixture : public testing::Test {
public:
    Memory mem{64};
    I8080 cpu{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    void SetUp() override {
        cpu.Reset(mem, 0xFFFC);
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
