#pragma once

#include <gtest/gtest.h>
#include "I8086_OpCodes_Main.h"
#include "ModRegConstructor.h"
#include "I8086.h"

class I8086_TestFixture : public testing::Test {
public:
    Memory mem{1024};
    I8086 cpu{};
    Bus bus{};

    U32 cyclesPassed;
    U32 cyclesExpected;
    DWORD effectiveAddress;

    void SetUp() override {
        mem.Reset();
        cpu.Reset();
        cpu.SetBusInstance(&bus);
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        effectiveAddress = cpu.PC + (cpu.CS << 4);
        cpu.GetBus()->SetBusRegion(0x0000, 0xFFFFFFFF, &mem);
    }

    void TearDown() override {
        std::printf("Cycles passed %d expected %d\n", cyclesPassed, cyclesExpected);
    }

    void CheckCyclesCount() const noexcept {
        EXPECT_EQ(cyclesPassed, cyclesExpected);
    }

    void CheckStatus(const I8086_Status &targetStatus) const {
        EXPECT_EQ(cpu.Status.C, targetStatus.C);
        EXPECT_EQ(cpu.Status.Z, targetStatus.Z);
        EXPECT_EQ(cpu.Status.P, targetStatus.P);
        EXPECT_EQ(cpu.Status.S, targetStatus.S);
    }
};
