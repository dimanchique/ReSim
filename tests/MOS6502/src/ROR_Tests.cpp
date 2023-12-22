#include "MOS6502_TestingSuite.h"

class MOS6502_RORFixture : public MOS6502_TestFixture {
public:
    void ROR_ACC_CanRollRight(BYTE value) {
        // given:
        cpu.A = value;
        mem[0xFFFC] = MOS6502_OpCodes::ROR_ACC;

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

    void ROR_ZP_CanRollRight(BYTE value) {
        // given:
        mem[0xFFFC] = MOS6502_OpCodes::ROR_ZP;
        mem[0xFFFD] = 0x42;
        mem[0x0042] = value;

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

    void ROR_ZPX_CanRollRight(BYTE value) {
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = MOS6502_OpCodes::ROR_ZPX;
        mem[0xFFFD] = 0x42;
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = value;

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

    void ROR_ABS_CanRollRight(BYTE value) {
        // given:
        mem[0xFFFC] = MOS6502_OpCodes::ROR_ABS;
        mem[0xFFFD] = 0x01;
        mem[0xFFFE] = 0x44;
        mem[0x4401] = value;

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

    void ROR_ABS_CanRollRight(MOS6502_OpCodes opcode, BYTE value, BYTE affectingRegister) {
        // given:
        mem[0xFFFC] = opcode;
        mem[0xFFFD] = 0x02;
        mem[0xFFFE] = 0x44;
        mem[0x4402 + affectingRegister] = value;

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
    ROR_ABS_CanRollRight(MOS6502_OpCodes::ROR_ABSX, 0xFF, cpu.X);
}

TEST_F(MOS6502_RORFixture, ROR_ABSX_CanAffectZeroFlag) {
    cpu.Status.C = 0;
    cpu.X = 0x05;
    ROR_ABS_CanRollRight(MOS6502_OpCodes::ROR_ABSX, 0x01, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}
