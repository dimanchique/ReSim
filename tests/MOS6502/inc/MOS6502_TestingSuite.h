#pragma once
#include <gtest/gtest.h>
#include "MOS6502/MOS6502_OpCodes.h"
#include "MOS6502/MOS6502.h"
#include "memory.h"

class MOS6502_TestFixture : public testing::Test {
public:
    Memory mem{64};
    MOS6502 cpu{};
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

    void SetStatusBitByMask(BYTE mask, BYTE value) {
        if (value)
            cpu.Status.Value |= mask;
        else
            cpu.Status.Value &= ~mask;
    }
};
