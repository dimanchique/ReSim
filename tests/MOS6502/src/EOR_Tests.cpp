#include "MOS6502_TestingSuite.h"

class MOS6502_EORFixture : public MOS6502_TestFixture {
public:
    void EOR_IM_CanLoadValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = MOS6502_OpCodes::EOR_IM;
        mem[0xFFFD] = memoryValue;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue ^ initialValue);
        CheckCyclesCount();
    }

    void EOR_ZP_CanLoadValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = MOS6502_OpCodes::EOR_ZP;
        mem[0xFFFD] = 0x42;
        mem[0x0042] = memoryValue;

        cyclesExpected = 3;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue ^ initialValue);
        CheckCyclesCount();
    }

    void EOR_ZPX_CanLoadValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        cpu.X = 0x10;
        mem[0xFFFC] = MOS6502_OpCodes::EOR_ZPX;
        mem[0xFFFD] = 0x42;
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = memoryValue;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue ^ initialValue);
        CheckCyclesCount();
    }

    void EOR_ABS_CanLoadValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = MOS6502_OpCodes::EOR_ABS;
        mem[0xFFFD] = 0x80;
        mem[0xFFFE] = 0x44;
        mem[0x4480] = memoryValue;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue ^ initialValue);
        CheckCyclesCount();
    }

    void EOR_ABS_CanLoadValue(MOS6502_OpCodes opcode, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = opcode;
        mem[0xFFFD] = 0x02;
        mem[0xFFFE] = 0x44;
        mem[0x4402 + affectingRegister] = memoryValue;

        cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue ^ initialValue);
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_EORFixture, EOR_IM_CanLoadValue) {
    EOR_IM_CanLoadValue(0xFF, 0xF);
}

TEST_F(MOS6502_EORFixture, EOR_IM_CanAffectZeroFlag) {
    EOR_IM_CanLoadValue(0xF, 0xF);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_IM_CanAffectNegativeFlag) {
    EOR_IM_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_ZP_CanLoadValue) {
    EOR_ZP_CanLoadValue(0xFF, 0xF);
}

TEST_F(MOS6502_EORFixture, EOR_ZP_CanAffectZeroFlag) {
    EOR_ZP_CanLoadValue(0xF, 0xF);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_ZP_CanAffectNegativeFlag) {
    EOR_ZP_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_ZPX_CanLoadValue) {
    EOR_ZPX_CanLoadValue(0xFF, 0xF);
}

TEST_F(MOS6502_EORFixture, EOR_ZPX_CanAffectZeroFlag) {
    EOR_ZPX_CanLoadValue(0xF, 0xF);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_ZPX_CanAffectNegativeFlag) {
    EOR_ZPX_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_ABS_CanLoadValue) {
    EOR_ABS_CanLoadValue(0xFF, 0xF);
}

TEST_F(MOS6502_EORFixture, EOR_ABS_CanAffectZeroFlag) {
    EOR_ABS_CanLoadValue(0xF, 0xF);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_ABS_CanAffectNegativeFlag) {
    EOR_ABS_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_ABSX_CanLoadValue) {
    cpu.X = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(MOS6502_EORFixture, EOR_ABSX_CanLoadValue_WithExtraCycleOnPageCrossing) {
    cpu.X = 0xFF;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(MOS6502_EORFixture, EOR_ABSX_CanAffectZeroFlag) {
    cpu.X = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSX, 0xF, 0xF, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_ABSX_CanAffectNegativeFlag) {
    cpu.X = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSX, 0xFF, 0x0, cpu.X);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_ABSY_CanLoadValue) {
    cpu.Y = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(MOS6502_EORFixture, EOR_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing) {
    cpu.Y = 0xFF;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(MOS6502_EORFixture, EOR_ABSY_CanAffectZeroFlag) {
    cpu.Y = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSY, 0xF, 0xF, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_EORFixture, EOR_ABSY_CanAffectNegativeFlag) {
    cpu.Y = 0x05;
    EOR_ABS_CanLoadValue(MOS6502_OpCodes::EOR_ABSY, 0xFF, 0x0, cpu.Y);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_EORFixture, EOR_INDX_CanLoadValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFFFC] = MOS6502_OpCodes::EOR_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address from 0x0006-0x0007
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x37;                         // do EOR with this value

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 ^ 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_EORFixture, EOR_INDY_CanLoadValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFFFC] = MOS6502_OpCodes::EOR_INDY;    // read the 8 bit value from the next mem cell
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (add Y) = 0x8004
    mem[0x8004] = 0x37;                         // do EOR with this value

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 ^ 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_EORFixture, EOR_INDY_CanLoadValue_WithExtraCycleOnPageCrossing) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0xFF;                               // preload FF to Y to add it to absolute address we read
    mem[0xFFFC] = MOS6502_OpCodes::EOR_INDY;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x02;                         //
    mem[0x0003] = 0x80;                         // 0x8002 + 0x00FF (Y) = 0x8101 -> page crossing, so we need extra cycle
    mem[0x8101] = 0x37;                         // do EOR with this value

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 ^ 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
