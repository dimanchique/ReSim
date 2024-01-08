#include "MOS6502_TestingSuite.h"

class MOS6502_ASLFixture : public MOS6502_TestFixture {
public:
    void ASL_ACC_CanDoShiftLeft(BYTE value) {
        // given:
        cpu.A = value;
        mem[0xFFFC] = MOS6502_OpCodes::ASL_ACC;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, BYTE(value << 1));
        CheckCyclesCount();
    }

    void ASL_ZP_CanDoShiftLeft(BYTE value) {
        // given:
        mem[0xFFFC] = MOS6502_OpCodes::ASL_ZP;
        mem[0xFFFD] = 0x42;
        mem[0x0042] = value;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x0042], BYTE(value << 1));
        CheckCyclesCount();
    }

    void ASL_ZPX_CanDoShiftLeft(BYTE value) {
        // given:
        cpu.X = 0x10;
        mem[0xFFFC] = MOS6502_OpCodes::ASL_ZPX;
        mem[0xFFFD] = 0x42;
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = value;

        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[(mem[0xFFFD] + cpu.X) & 0xFF], BYTE(value << 1));
        CheckCyclesCount();
    }

    void ASL_ABS_CanDoShiftLeft(BYTE value) {
        // given:
        mem[0xFFFC] = MOS6502_OpCodes::ASL_ABS;
        mem[0xFFFD] = 0x80;
        mem[0xFFFE] = 0x44;
        mem[0x4480] = value;

        cyclesExpected = 6;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4480], BYTE(value << 1));
        CheckCyclesCount();
    }

    void ASL_ABS_CanDoShiftLeft(MOS6502_OpCodes opcode, BYTE value, BYTE affectingRegister) {
        // given:
        mem[0xFFFC] = opcode;
        mem[0xFFFD] = 0x02;
        mem[0xFFFE] = 0x44;
        mem[0x4402 + affectingRegister] = value;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[0x4402 + affectingRegister], BYTE(value << 1));
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_ASLFixture, ASL_ACC_CanDoShiftLeft) {
    ASL_ACC_CanDoShiftLeft(0xFF);
}

TEST_F(MOS6502_ASLFixture, ASL_ACC_CanAffectZeroFlag) {
    ASL_ACC_CanDoShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ASLFixture, ASL_ACC_CanAffectNegativeFlag) {
    ASL_ACC_CanDoShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ASLFixture, ASL_ZP_CanDoShiftLeft) {
    ASL_ZP_CanDoShiftLeft(0xFF);
}

TEST_F(MOS6502_ASLFixture, ASL_ZP_CanAffectZeroFlag) {
    ASL_ZP_CanDoShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ASLFixture, ASL_ZP_CanAffectNegativeFlag) {
    ASL_ZP_CanDoShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ASLFixture, ASL_ZPX_CanDoShiftLeft) {
    ASL_ZPX_CanDoShiftLeft(0xFF);
}

TEST_F(MOS6502_ASLFixture, ASL_ZPX_CanAffectZeroFlag) {
    ASL_ZPX_CanDoShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ASLFixture, ASL_ZPX_CanAffectNegativeFlag) {
    ASL_ZPX_CanDoShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ASLFixture, ASL_ABS_CanDoShiftLeft) {
    ASL_ABS_CanDoShiftLeft(0xFF);
}

TEST_F(MOS6502_ASLFixture, ASL_ABS_CanAffectZeroFlag) {
    ASL_ABS_CanDoShiftLeft(0x80);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ASLFixture, ASL_ABS_CanAffectNegativeFlag) {
    ASL_ABS_CanDoShiftLeft(0x40);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ASLFixture, ASL_ABSX_CanDoShiftLeft) {
    cpu.X = 0x05;
    ASL_ABS_CanDoShiftLeft(MOS6502_OpCodes::ASL_ABSX, 0xFF, cpu.X);
}

TEST_F(MOS6502_ASLFixture, ASL_ABSX_CanAffectZeroFlag) {
    cpu.X = 0x05;
    ASL_ABS_CanDoShiftLeft(MOS6502_OpCodes::ASL_ABSX, 0x80, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ASLFixture, ASL_ABSX_CanAffectNegativeFlag) {
    cpu.X = 0x05;
    ASL_ABS_CanDoShiftLeft(MOS6502_OpCodes::ASL_ABSX, 0x40, cpu.X);
    EXPECT_TRUE(cpu.Status.N);
}
