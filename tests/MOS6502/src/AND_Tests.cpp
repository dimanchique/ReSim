#include "MOS6502_TestingSuite.h"

class MOS6502_ANDFixture : public MOS6502_TestFixture {
public:
    void AND_IM_CanDoAND(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = AND_IM;
        mem[0xFF01] = memoryValue;
        mem[0xFF02] = STOP_OPCODE;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue & initialValue);
        CheckCyclesCount();
    }

    void AND_ZP_CanDoAND(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = AND_ZP;
        mem[0xFF01] = 0x42;
        mem[0xFF02] = STOP_OPCODE;
        mem[0x0042] = memoryValue;

        cyclesExpected = 3;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue & initialValue);
        CheckCyclesCount();
    }

    void AND_ZPX_CanDoAND(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        cpu.X = 0x10;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = AND_ZPX;
        mem[0xFF01] = 0x42;
        mem[0xFF02] = STOP_OPCODE;
        mem[(mem[0xFF01] + cpu.X) & 0xFF] = memoryValue;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue & initialValue);
        CheckCyclesCount();
    }

    void AND_ABS_CanDoAND(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = AND_ABS;
        mem[0xFF01] = 0x80;
        mem[0xFF02] = 0x44;
        mem[0xFF03] = STOP_OPCODE;
        mem[0x4480] = memoryValue;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue & initialValue);
        CheckCyclesCount();
    }

    void AND_ABS_CanDoAND(MOS6502_OpCodes opcode, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = opcode;
        mem[0xFF01] = 0x02;
        mem[0xFF02] = 0x44;
        mem[0xFF03] = STOP_OPCODE;
        mem[0x4402 + affectingRegister] = memoryValue;

        cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue & initialValue);
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_ANDFixture, AND_IM_CanDoAND) {
    AND_IM_CanDoAND(0xFF, 0xF);
}

TEST_F(MOS6502_ANDFixture, AND_IM_CanAffectZeroFlag) {
    AND_IM_CanDoAND(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_IM_CanAffectNegativeFlag) {
    AND_IM_CanDoAND(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_ZP_CanDoAND) {
    AND_ZP_CanDoAND(0xFF, 0xF);
}

TEST_F(MOS6502_ANDFixture, AND_ZP_CanAffectZeroFlag) {
    AND_ZP_CanDoAND(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_ZP_CanAffectNegativeFlag) {
    AND_ZP_CanDoAND(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_ZPX_CanDoAND) {
    AND_ZPX_CanDoAND(0xFF, 0xF);
}

TEST_F(MOS6502_ANDFixture, AND_ZPX_CanAffectZeroFlag) {
    AND_ZPX_CanDoAND(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_ZPX_CanAffectNegativeFlag) {
    AND_ZPX_CanDoAND(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_ABS_CanDoAND) {
    AND_ABS_CanDoAND(0xFF, 0xF);
}

TEST_F(MOS6502_ANDFixture, AND_ABS_CanAffectZeroFlag) {
    AND_ABS_CanDoAND(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_ABS_CanAffectNegativeFlag) {
    AND_ABS_CanDoAND(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_ABSX_CanDoAND) {
    cpu.X = 0x05;
    AND_ABS_CanDoAND(AND_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(MOS6502_ANDFixture, AND_ABSX_CanDoAND_WithExtraCycleOnPageCrossing) {
    cpu.X = 0xFF;
    AND_ABS_CanDoAND(AND_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(MOS6502_ANDFixture, AND_ABSX_CanAffectZeroFlag) {
    cpu.X = 0x05;
    AND_ABS_CanDoAND(AND_ABSX, 0xFF, 0x0, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_ABSX_CanAffectNegativeFlag) {
    cpu.X = 0x05;
    AND_ABS_CanDoAND(AND_ABSX, 0xFF, 0xFF, cpu.X);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_ABSY_CanDoAND) {
    cpu.Y = 0x05;
    AND_ABS_CanDoAND(AND_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(MOS6502_ANDFixture, AND_ABSY_CanDoAND_WithExtraCycleOnPageCrossing) {
    cpu.Y = 0xFF;
    AND_ABS_CanDoAND(AND_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(MOS6502_ANDFixture, AND_ABSY_CanAffectZeroFlag) {
    cpu.Y = 0x05;
    AND_ABS_CanDoAND(AND_ABSY, 0xFF, 0x0, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_ANDFixture, AND_ABSY_CanAffectNegativeFlag) {
    cpu.Y = 0x05;
    AND_ABS_CanDoAND(AND_ABSY, 0xFF, 0xFF, cpu.Y);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_ANDFixture, AND_INDX_CanDoAND) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    cpu.A = 0x42;
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFF00] = AND_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFF01] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0xFF02] = STOP_OPCODE;                  //
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address from 0x0006-0x0007
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x37;                         // do AND with this value

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ANDFixture, AND_INDY_CanDoAND) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    cpu.A = 0x42;
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFF00] = AND_INDY;    // read the 8 bit value from the next mem cell
    mem[0xFF01] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0xFF02] = STOP_OPCODE;                  //
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (add Y) = 0x8004
    mem[0x8004] = 0x37;                         // do AND with this value

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ANDFixture, AND_INDY_CanDoAND_WithExtraCycleOnPageCrossing) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    cpu.A = 0x42;
    cpu.Y = 0xFF;                               // preload FF to Y to add it to absolute address we read
    mem[0xFF00] = AND_INDY;    // read the 8 bit value from the next mem cell and add X
    mem[0xFF01] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0xFF02] = STOP_OPCODE;                  //
    mem[0x0002] = 0x02;                         //
    mem[0x0003] = 0x80;                         // 0x8002 + 0x00FF (Y) = 0x8101 -> page crossing, so we need extra cycle
    mem[0x8101] = 0x37;                         // do AND with this value

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
