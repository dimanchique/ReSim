#include "CPU6502_TestingSuite.h"

class CPU6502_ASLFixture : public CPU6502_TestFixture{
public:
    void ASL_ACC_CanShiftLeft(BYTE Value){
        // given:
        cpu.A = Value;
        mem[0xFFFC] = CPU6502_OpCodes::ASL_ACC;                     // shift left

        CyclesExpected = 2;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, BYTE(Value << 1));
        CheckCyclesCount();
    }

    void ASL_ZP_CanShiftLeft(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ASL_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = Value;                                        // store this value in target register

        CyclesExpected = 5;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], BYTE(Value << 1));
        CheckCyclesCount();
    }

    void ASL_ZPX_CanShiftLeft(BYTE Value){
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::ASL_ZPX;                     // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // add AffectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = Value;                  // read value from memory using pointer
        // store this value in TargetRegister register
        CyclesExpected = 6;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], BYTE(Value << 1));
        CheckCyclesCount();
    }

    void ASL_ABS_CanShiftLeft(BYTE Value){
        // given:
        mem[0xFFFC] = CPU6502_OpCodes::ASL_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x80;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4480
        mem[0x4480] = Value;                        // store this value in TargetRegister

        CyclesExpected = 6;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4480], BYTE(Value << 1));
        CheckCyclesCount();
    }

    void ASL_ABS_CanShiftLeft(CPU6502_OpCodes OpCode, BYTE Value, BYTE AffectingRegister){
        // given:
        mem[0xFFFC] = OpCode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + AffectingRegister
        mem[0x4402 + AffectingRegister] = Value;        // store this value in TargetRegister

        CyclesExpected = 7;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + AffectingRegister], BYTE(Value << 1));
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_ASLFixture, ASL_ACC_CanShiftLeft){
    ASL_ACC_CanShiftLeft(0xFF);
}

TEST_F(CPU6502_ASLFixture, ASL_ACC_CanAffectZeroFlag){
    ASL_ACC_CanShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_ASLFixture, ASL_ACC_CanAffectNegativeFlag){
    ASL_ACC_CanShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ASLFixture, ASL_ZP_CanShiftLeft){
    ASL_ZP_CanShiftLeft(0xFF);
}

TEST_F(CPU6502_ASLFixture, ASL_ZP_CanAffectZeroFlag){
    ASL_ZP_CanShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_ASLFixture, ASL_ZP_CanAffectNegativeFlag){
    ASL_ZP_CanShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ASLFixture, ASL_ZPX_CanShiftLeft){
    ASL_ZPX_CanShiftLeft(0xFF);
}

TEST_F(CPU6502_ASLFixture, ASL_ZPX_CanAffectZeroFlag){
    ASL_ZPX_CanShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_ASLFixture, ASL_ZPX_CanAffectNegativeFlag){
    ASL_ZPX_CanShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ASLFixture, ASL_ABS_CanShiftLeft){
    ASL_ABS_CanShiftLeft(0xFF);
}

TEST_F(CPU6502_ASLFixture, ASL_ABS_CanAffectZeroFlag){
    ASL_ABS_CanShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_ASLFixture, ASL_ABS_CanAffectNegativeFlag){
    ASL_ABS_CanShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ASLFixture, ASL_ABSX_CanShiftLeft){
    cpu.X = 0x05;
    ASL_ABS_CanShiftLeft(CPU6502_OpCodes::ASL_ABSX, 0xFF, cpu.X);
}

TEST_F(CPU6502_ASLFixture, ASL_ABSX_CanAffectZeroFlag){
    cpu.X = 0x05;
    ASL_ABS_CanShiftLeft(CPU6502_OpCodes::ASL_ABSX, 0x80, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_ASLFixture, ASL_ABSX_CanAffectNegativeFlag){
    cpu.X = 0x05;
    ASL_ABS_CanShiftLeft(CPU6502_OpCodes::ASL_ABSX, 0x40, cpu.X);
    EXPECT_TRUE(cpu.Status.N);
}
