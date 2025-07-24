#pragma once
#include <gtest/gtest.h>
#include "I8080_OpCodes.h"
#include "I8080.h"
#include "memory.h"

class I8080_TestFixture : public testing::Test {
public:
    Memory mem{64};
    I8080 cpu{};
    Bus bus{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    void SetUp() override {
        mem.Reset();
        cpu.Reset();
        cpu.SetBusInstance(&bus);
        cpu.GetBus()->SetBusRegion(0x0000, 0xFFFF, &mem);
    }

    void TearDown() override {
        std::printf("Cycles passed %d expected %d\n", cyclesPassed, cyclesExpected);
    }

    void CheckCyclesCount() const noexcept {
        EXPECT_EQ(cyclesPassed, cyclesExpected);
    }

    void CheckStatus(const I8080_Status &targetStatus){
        EXPECT_EQ(cpu.Status.C, targetStatus.C);
        EXPECT_EQ(cpu.Status.Z, targetStatus.Z);
        EXPECT_EQ(cpu.Status.AC, targetStatus.AC);
        EXPECT_EQ(cpu.Status.P, targetStatus.P);
        EXPECT_EQ(cpu.Status.S, targetStatus.S);
    }
};
