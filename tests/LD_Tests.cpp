#include "CPU6502_LD_Tests.h"

void CPU6502_LDFixture::LD_IM_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    BYTE OldValue = 0x44;
    BYTE NewValue = 0x04;
    targetRegister = OldValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = NewValue;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(targetRegister, OldValue);
    EXPECT_EQ(targetRegister, NewValue);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_IM_CanAffectZeroFlag(CPU6502_OpCodes opcode) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x0;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes opcode) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x80;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x37;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x42;
    mem[(mem[0xFFFD] + affectingRegister) & 0xFF] = 0x37;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x80;
    mem[0xFFFE] = 0x44;
    mem[0x4480] = 0x37;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + affectingRegister] = 0x37;

    cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
