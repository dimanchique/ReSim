#include "MOS6502_TestingSuite.h"

class MOS6502_RORFixture : public MOS6502_TestFixture {
public:
    void ROR_ACC_CanRollRight(BYTE value) {
        // given:
        cpu.A = value;
        mem[effectiveAddress++] = ROR_ACC;
        mem[effectiveAddress++] = RTS_IMPL;

        cyclesExpected = 2;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(cpu.A, NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ZP_CanRollRight(BYTE value) {
        // given:
        mem[effectiveAddress++] = ROR_ZP;
        mem[effectiveAddress++] = 0x42;
        mem[effectiveAddress++] = RTS_IMPL;
        mem[0x0042] = value;

        cyclesExpected = 5;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(mem[0x0042], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ZPX_CanRollRight(BYTE value) {
        // given:
        cpu.X = 0x10;
        mem[effectiveAddress++] = ROR_ZPX;
        mem[effectiveAddress++] = 0x42;
        mem[effectiveAddress++] = RTS_IMPL;
        mem[(0x42 + cpu.X) & 0xFF] = value;

        cyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(mem[(0x42 + cpu.X) & 0xFF], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ABS_CanRollRight(BYTE value) {
        // given:
        mem[effectiveAddress++] = ROR_ABS;
        mem[effectiveAddress++] = 0x01;
        mem[effectiveAddress++] = 0x44;
        mem[effectiveAddress++] = RTS_IMPL;
        mem[0x4401] = value;

        cyclesExpected = 6;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(mem[0x4401], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }

    void ROR_ABS_CanRollRight(MOS6502_OpCodes_Main opcode, BYTE value, BYTE affectingRegister) {
        // given:
        WORD targetAddress = 0x4200;
        WORD displacedAddress = targetAddress + affectingRegister;

        mem[effectiveAddress++] = opcode;
        mem[effectiveAddress++] = targetAddress & 0xFF;
        mem[effectiveAddress++] = (targetAddress >> 8) & 0xFF;
        mem[effectiveAddress++] = RTS_IMPL;
        mem[displacedAddress] = value;

        cyclesExpected = 7;
        BYTE OldCarry = cpu.Status.C;
        BYTE NewCarry = value & 1;
        BYTE NewA = BYTE(value >> 1) | (OldCarry << 7);

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(mem[displacedAddress], NewA);
        EXPECT_EQ(cpu.Status.C, NewCarry);
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_RORFixture, ROR_ACC_CanRollRight) {
    cpu.Status.C = 1;
    ROR_ACC_CanRollRight(0xFF);
}

TEST_F(MOS6502_RORFixture, ROR_ACC_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    ROR_ACC_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_RORFixture, ROR_ZP_CanRollRight) {
    cpu.Status.C = 1;
    ROR_ZP_CanRollRight(0xFF);
}

TEST_F(MOS6502_RORFixture, ROR_ZP_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    ROR_ZP_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_RORFixture, ROR_ZPX_CanRollRight) {
    cpu.Status.C = 1;
    ROR_ZPX_CanRollRight(0xFF);
}

TEST_F(MOS6502_RORFixture, ROR_ZPX_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    ROR_ZPX_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_RORFixture, ROR_ABS_CanRollRight) {
    cpu.Status.C = 1;
    ROR_ABS_CanRollRight(0xFF);
}

TEST_F(MOS6502_RORFixture, ROR_ABS_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    ROR_ABS_CanRollRight(0x01);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_RORFixture, ROR_ABSX_CanRollRight) {
    cpu.Status.C = 1;
    cpu.X = 0x05;
    ROR_ABS_CanRollRight(ROR_ABSX, 0xFF, cpu.X);
}

TEST_F(MOS6502_RORFixture, ROR_ABSX_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    cpu.X = 0x05;
    ROR_ABS_CanRollRight(ROR_ABSX, 0x01, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
