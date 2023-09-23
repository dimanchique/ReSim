#include "CPU6502_TestingSuite.h"

class CPU6502_RORFixture : public CPU6502_TestFixture{
public:
    void ROR_ACC_CanRollRight(BYTE value){
        // given:
        cpu.A = value;
        mem[0xFFFC] = CPU6502_OpCodes::ROR_ACC;                     // roll left

        cyclesExpected = 2;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ZP_CanRollRight(BYTE value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ROR_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = value;                                        // store this value in target register

        cyclesExpected = 5;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ZPX_CanRollRight(BYTE value){
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::ROR_ZPX;                     // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // add affectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = value;                  // read value from memory using pointer
        // store this value in targetRegister register
        cyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ABS_CanRollRight(BYTE value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ROR_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x01;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4401
        mem[0x4401] = value;                        // store this value in targetRegister

        cyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4401], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ABS_CanRollRight(CPU6502_OpCodes opcode, BYTE value, BYTE affectingRegister){
        // given:
        mem[0xFFFC] = opcode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + affectingRegister
        mem[0x4402 + affectingRegister] = value;        // store this value in targetRegister

        cyclesExpected = 7;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + affectingRegister], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_RORFixture, ROR_ACC_CanRollRight){
    cpu.Status.C = 1;
    ROR_ACC_CanRollRight(0xFF);
}

TEST_F(CPU6502_RORFixture, ROR_ACC_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROR_ACC_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_RORFixture, ROR_ZP_CanRollRight){
    cpu.Status.C = 1;
    ROR_ZP_CanRollRight(0xFF);
}

TEST_F(CPU6502_RORFixture, ROR_ZP_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROR_ZP_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_RORFixture, ROR_ZPX_CanRollRight){
    cpu.Status.C = 1;
    ROR_ZPX_CanRollRight(0xFF);
}

TEST_F(CPU6502_RORFixture, ROR_ZPX_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROR_ZPX_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_RORFixture, ROR_ABS_CanRollRight){
    cpu.Status.C = 1;
    ROR_ABS_CanRollRight(0xFF);
}

TEST_F(CPU6502_RORFixture, ROR_ABS_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROR_ABS_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_RORFixture, ROR_ABSX_CanRollRight){
    cpu.Status.C = 1;
    cpu.X = 0x05;
    ROR_ABS_CanRollRight(CPU6502_OpCodes::ROR_ABSX, 0xFF, cpu.X);
}

TEST_F(CPU6502_RORFixture, ROR_ABSX_CanAffectZeroFlag){
    cpu.Status.C = 0;
    cpu.X = 0x05;
    ROR_ABS_CanRollRight(CPU6502_OpCodes::ROR_ABSX, 0x01, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
