#include "CPU6502_TestingSuite.h"

class CPU6502_LSRFixture : public CPU6502_TestFixture{
public:
    void LSR_ACC_CanShiftRight(BYTE Value){
        // given:
        cpu.A = Value;
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ACC;                     // shift right

        CyclesExpected = 2;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, BYTE(Value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZP_CanShiftRight(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = Value;                                        // store this value in target register

        CyclesExpected = 5;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], BYTE(Value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZPX_CanShiftRight(BYTE Value){
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ZPX;                     // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // add AffectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = Value;                  // read value from memory using pointer
        // store this value in TargetRegister register
        CyclesExpected = 6;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], BYTE(Value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x01;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4401
        mem[0x4401] = Value;                        // store this value in TargetRegister

        CyclesExpected = 6;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4401], BYTE(Value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(CPU6502_OpCodes OpCode, BYTE Value, BYTE AffectingRegister){
        // given:
        mem[0xFFFC] = OpCode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + AffectingRegister
        mem[0x4402 + AffectingRegister] = Value;        // store this value in TargetRegister

        CyclesExpected = 7;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + AffectingRegister], BYTE(Value >> 1));
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_LSRFixture, LSR_ACC_CanShiftRight){
    LSR_ACC_CanShiftRight(0xFF);
}

TEST_F(CPU6502_LSRFixture, LSR_ACC_CanAffectZeroFlag){
    LSR_ACC_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_LSRFixture, LSR_ZP_CanShiftRight){
    LSR_ZP_CanShiftRight(0xFF);
}

TEST_F(CPU6502_LSRFixture, LSR_ZP_CanAffectZeroFlag){
    LSR_ZP_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_LSRFixture, LSR_ZPX_CanShiftRight){
    LSR_ZPX_CanShiftRight(0xFF);
}

TEST_F(CPU6502_LSRFixture, LSR_ZPX_CanAffectZeroFlag){
    LSR_ZPX_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_LSRFixture, LSR_ABS_CanShiftRight){
    LSR_ABS_CanShiftRight(0xFF);
}

TEST_F(CPU6502_LSRFixture, LSR_ABS_CanAffectZeroFlag){
    LSR_ABS_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_LSRFixture, LSR_ABSX_CanShiftRight){
    cpu.X = 0x05;
    LSR_ABS_CanShiftRight(CPU6502_OpCodes::LSR_ABSX, 0xFF, cpu.X);
}

TEST_F(CPU6502_LSRFixture, LSR_ABSX_CanAffectZeroFlag){
    cpu.X = 0x05;
    LSR_ABS_CanShiftRight(CPU6502_OpCodes::LSR_ABSX, 0x01, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
