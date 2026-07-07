#pragma once

#include <gtest/gtest.h>
#include "I8086_OpCodes_Main.h"
#include "ModRegConstructor.h"
#include "I8086.h"

class I8086_TestFixture : public testing::Test {
public:
    Memory<DWORD> mem{1024};
    I8086 cpu{};
    Bus<DWORD> bus{};

    U32 cyclesPassed;
    U32 cyclesExpected;
    DWORD effectiveAddress;

    void SetUp() override {
        mem.Reset();
        cpu.Reset();
        bus.Attach(&mem, 0x0000, 0xFFFFFFFF);
        cpu.SetBusInstance(&bus);
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        effectiveAddress = EFFECTIVE_ADDRESS(cpu.PC, cpu.CS);
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
