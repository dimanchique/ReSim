#include "CPU6502_TestingSuite.h"

class CPU6502_LSRFixture : public CPU6502_TestFixture{
public:
    void LSR_ACC_CanShiftRight(BYTE value){
        // given:
        cpu.A = value;
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ACC;                     // shift right

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZP_CanShiftRight(BYTE value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = value;                                        // store this value in target register

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZPX_CanShiftRight(BYTE value){
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ZPX;                     // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // add affectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = value;                  // read value from memory using pointer
        // store this value in targetRegister register
        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(BYTE value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::LSR_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x01;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4401
        mem[0x4401] = value;                        // store this value in targetRegister

        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4401], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(CPU6502_OpCodes opcode, BYTE value, BYTE affectingRegister){
        // given:
        mem[0xFFFC] = opcode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + affectingRegister
        mem[0x4402 + affectingRegister] = value;        // store this value in targetRegister

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + affectingRegister], BYTE(value >> 1));
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
