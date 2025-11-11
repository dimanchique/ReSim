#include "MOS6502_LD_Tests.h"

void MOS6502_LDFixture::LD_IM_CanLoadValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister) {
    // given:
    BYTE OldValue = 0x44;
    BYTE NewValue = 0x04;
    targetRegister = OldValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = NewValue;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_NE(targetRegister, OldValue);
    EXPECT_EQ(targetRegister, NewValue);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_IM_CanAffectZeroFlag(MOS6502_OpCodes_Main opcode) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x0;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_IM_CanAffectNegativeFlag(MOS6502_OpCodes_Main opcode) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x80;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_ZP_CanLoadValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x0042] = 0x37;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_ZP_CanLoadValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE affectingRegister) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[(0x42 + affectingRegister) & 0xFF] = 0x37;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_ABS_CanLoadValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x80;
    mem[effectiveAddress++] = 0x44;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x4480] = 0x37;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void MOS6502_LDFixture::LD_ABS_CanLoadValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE affectingRegister) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x02;
    mem[effectiveAddress++] = 0x44;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x4402 + affectingRegister] = 0x37;

    cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
