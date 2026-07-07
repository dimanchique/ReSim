#pragma once
#include <gtest/gtest.h>
#include "MOS6502_OpCodes_Main.h"
#include "MOS6502.h"

class MOS6502_TestFixture : public testing::Test {
public:
    Memory<WORD> mem{64};
    MOS6502 cpu{};
    Bus<WORD> bus{};

    U32 cyclesPassed;
    U32 cyclesExpected;

    WORD effectiveAddress = 0xFF00;

    void SetUp() override {
        mem.Reset();
        cpu.Reset();
        bus.Attach(&mem, 0x0000, 0xFFFF);
        cpu.SetBusInstance(&bus);

        mem[0xFFFC] = effectiveAddress & 0xFF;
        mem[0xFFFD] = (effectiveAddress >> 8) & 0xFF;
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
