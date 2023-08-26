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

    void LD_IM_CanLoadValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister){
        // given:
        BYTE OldValue = 0x44;
        BYTE NewValue = 0x04;
        TargetRegister = OldValue;
        mem[0xFFFC] = OpCode;                           // read value from the next mem cell
        mem[0xFFFD] = NewValue;                         // store this value in target register

        // when:
        cpu.Run(2, mem);

        // then:
        EXPECT_NE(TargetRegister, OldValue);
        EXPECT_EQ(TargetRegister, NewValue);
    }

    void LD_IM_CanAffectZeroFlag(CPU6502_OpCodes OpCode){
        // given:
        mem[0xFFFC] = OpCode;                       // read value from the next mem cell
        mem[0xFFFD] = 0x0;                          // store this value in target register

        // when:
        cpu.Run(2, mem);

        // then:
        EXPECT_TRUE(cpu.Z);
        EXPECT_FALSE(cpu.N);
    }

    void LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes OpCode){
        // given:
        mem[0xFFFC] = OpCode;                       // read value from the next mem cell
        mem[0xFFFD] = 0x80;                         // store this value in target register

        // when:
        cpu.Run(2, mem);

        // then:
        EXPECT_FALSE(cpu.Z);
        EXPECT_TRUE(cpu.N);
    }

    void LD_ZP_CanLoadValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister){
        // given:
        mem[0xFFFC] = OpCode;                       // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                         // read value from memory using pointer
        mem[0x0042] = 0x37;                         // store this value in target register

        const U32 NumCycles = 3;

        // when:
        U32 CNT = cpu.Run(NumCycles, mem);

        // then:
        EXPECT_EQ(TargetRegister, 0x37);
        EXPECT_FALSE(cpu.Z);
        EXPECT_FALSE(cpu.N);
        EXPECT_EQ(CNT, NumCycles);
    }

    void CheckUnmodifiedFlagsFromLoadOperation(const CPU6502& cpuCopy) const{
        EXPECT_EQ(cpu.C, cpuCopy.C);
        EXPECT_EQ(cpu.I, cpuCopy.I);
        EXPECT_EQ(cpu.D, cpuCopy.D);
        EXPECT_EQ(cpu.B, cpuCopy.B);
        EXPECT_EQ(cpu.V, cpuCopy.V);
    }
};

