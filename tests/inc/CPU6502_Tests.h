#pragma once

#include <gtest/gtest.h>
#include "CPU6502_OpCodes.h"
#include "CPU6502.h"
#include "Memory.h"

class CPU6502_TestFixture : public testing::Test{
public:
    Memory mem{64};
    CPU6502 cpu{};

    void SetUp() override{
        cpu.Reset(mem);
    }

    void TearDown() override{

    }
};

static void VerifyUnmodifiedFlagsFromLDA(const CPU6502& cpu, const CPU6502& cpuCopy){
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
}