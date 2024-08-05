#pragma once
#include <gtest/gtest.h>
#include "I8080/I8080_OpCodes.h"
#include "I8080/I8080.h"
#include "base/memory.h"

class I8080_TestFixture : public testing::Test {
public:
    Memory mem{64};
    I8080 cpu{};

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

    void CheckStatus(const I8080_Status &targetStatus){
        EXPECT_EQ(cpu.Status.C, targetStatus.C);
        EXPECT_EQ(cpu.Status.Z, targetStatus.Z);
        EXPECT_EQ(cpu.Status.AC, targetStatus.AC);
        EXPECT_EQ(cpu.Status.P, targetStatus.P);
        EXPECT_EQ(cpu.Status.S, targetStatus.S);
    }
};
