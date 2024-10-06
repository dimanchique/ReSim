#include "MOS6502_TestingSuite.h"

class MOS6502_LSRFixture : public MOS6502_TestFixture {
public:
    void LSR_ACC_CanShiftRight(BYTE value) {
        // given:
        cpu.A = value;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = LSR_ACC;
        mem[0xFF01] = STOP_OPCODE;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZP_CanShiftRight(BYTE value) {
        // given:
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = LSR_ZP;
        mem[0xFF01] = 0x42;
        mem[0xFF02] = STOP_OPCODE;
        mem[0x0042] = value;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ZPX_CanShiftRight(BYTE value) {
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = LSR_ZPX;
        mem[0xFF01] = 0x42;
        mem[0xFF02] = STOP_OPCODE;
        mem[(mem[0xFF01] + cpu.X) & 0xFF] = value;

        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFF01] + cpu.X) & 0xFF], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(BYTE value) {
        // given:
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = LSR_ABS;
        mem[0xFF01] = 0x01;
        mem[0xFF02] = 0x44;
        mem[0xFF03] = STOP_OPCODE;
        mem[0x4401] = value;

        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4401], BYTE(value >> 1));
        CheckCyclesCount();
    }

    void LSR_ABS_CanShiftRight(MOS6502_OpCodes opcode, BYTE value, BYTE affectingRegister) {
        // given:
        WORD targetAddress = 0x4402;
        WORD displacedAddress = targetAddress + affectingRegister;

        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = opcode;
        mem[0xFF01] = targetAddress & 0xFF;
        mem[0xFF02] = (targetAddress >> 8) & 0xFF;
        mem[0xFF03] = STOP_OPCODE;
        mem[displacedAddress] = value;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[displacedAddress], BYTE(value >> 1));
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_LSRFixture, LSR_ACC_CanShiftRight) {
    LSR_ACC_CanShiftRight(0xFF);
}

TEST_F(MOS6502_LSRFixture, LSR_ACC_CanAffectZeroFlag) {
    LSR_ACC_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_LSRFixture, LSR_ZP_CanShiftRight) {
    LSR_ZP_CanShiftRight(0xFF);
}

TEST_F(MOS6502_LSRFixture, LSR_ZP_CanAffectZeroFlag) {
    LSR_ZP_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_LSRFixture, LSR_ZPX_CanShiftRight) {
    LSR_ZPX_CanShiftRight(0xFF);
}

TEST_F(MOS6502_LSRFixture, LSR_ZPX_CanAffectZeroFlag) {
    LSR_ZPX_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_LSRFixture, LSR_ABS_CanShiftRight) {
    LSR_ABS_CanShiftRight(0xFF);
}

TEST_F(MOS6502_LSRFixture, LSR_ABS_CanAffectZeroFlag) {
    LSR_ABS_CanShiftRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_LSRFixture, LSR_ABSX_CanShiftRight) {
    cpu.X = 0x05;
    LSR_ABS_CanShiftRight(LSR_ABSX, 0xFF, cpu.X);
}

TEST_F(MOS6502_LSRFixture, LSR_ABSX_CanAffectZeroFlag) {
    cpu.X = 0x05;
    LSR_ABS_CanShiftRight(LSR_ABSX, 0x01, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
