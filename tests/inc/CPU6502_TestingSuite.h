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
