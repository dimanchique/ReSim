#include "CPU6502_TestingSuite.h"

class CPU6502_ROLFixture : public CPU6502_TestFixture{
public:
    void ROL_ACC_CanRollLeft(BYTE Value){
        // given:
        cpu.A = Value;
        mem[0xFFFC] = CPU6502_OpCodes::ROL_ACC;                     // roll left

        CyclesExpected = 2;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = (Value >> 7) & 1;
        BYTE NewA = BYTE(Value << 1) | OldCarry;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROL_ZP_CanRollLeft(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ROL_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = Value;                                        // store this value in target register

        CyclesExpected = 5;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = (Value >> 7) & 1;
        BYTE NewA = BYTE(Value << 1) | OldCarry;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROL_ZPX_CanRollLeft(BYTE Value){
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::ROL_ZPX;                     // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // add AffectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = Value;                  // read value from memory using pointer
        // store this value in TargetRegister register
        CyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = (Value >> 7) & 1;
        BYTE NewA = BYTE(Value << 1) | OldCarry;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROL_ABS_CanRollLeft(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ROL_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x01;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4401
        mem[0x4401] = Value;                        // store this value in TargetRegister

        CyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = (Value >> 7) & 1;
        BYTE NewA = BYTE(Value << 1) | OldCarry;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4401], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROL_ABS_CanRollLeft(CPU6502_OpCodes OpCode, BYTE Value, BYTE AffectingRegister){
        // given:
        mem[0xFFFC] = OpCode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + AffectingRegister
        mem[0x4402 + AffectingRegister] = Value;        // store this value in TargetRegister

        CyclesExpected = 7;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = (Value >> 7) & 1;
        BYTE NewA = BYTE(Value << 1) | OldCarry;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + AffectingRegister], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_ROLFixture, ROL_ACC_CanRollLeft){
    cpu.Status.C = 1;
    ROL_ACC_CanRollLeft(0xFF);
}

TEST_F(CPU6502_ROLFixture, ROL_ACC_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROL_ACC_CanRollLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ROLFixture, ROL_ZP_CanRollLeft){
    cpu.Status.C = 1;
    ROL_ZP_CanRollLeft(0xFF);
}

TEST_F(CPU6502_ROLFixture, ROL_ZP_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROL_ZP_CanRollLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ROLFixture, ROL_ZPX_CanRollLeft){
    cpu.Status.C = 1;
    ROL_ZPX_CanRollLeft(0xFF);
}

TEST_F(CPU6502_ROLFixture, ROL_ZPX_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROL_ZPX_CanRollLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ROLFixture, ROL_ABS_CanRollLeft){
    cpu.Status.C = 1;
    ROL_ABS_CanRollLeft(0xFF);
}

TEST_F(CPU6502_ROLFixture, ROL_ABS_CanAffectZeroFlag){
    cpu.Status.C = 0;
    ROL_ABS_CanRollLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ROLFixture, ROL_ABSX_CanRollLeft){
    cpu.Status.C = 1;
    cpu.X = 0x05;
    ROL_ABS_CanRollLeft(CPU6502_OpCodes::ROL_ABSX, 0xFF, cpu.X);
}

TEST_F(CPU6502_ROLFixture, ROL_ABSX_CanAffectZeroFlag){
    cpu.Status.C = 0;
    cpu.X = 0x05;
    ROL_ABS_CanRollLeft(CPU6502_OpCodes::ROL_ABSX, 0x80, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
