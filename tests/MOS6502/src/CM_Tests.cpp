#include "MOS6502_CM_Tests.h"

void MOS6502_CMFixture::CM_IM_CanCompare(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = memoryValue;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP_CanCompare(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x0042] = memoryValue;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP_CanCompare(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[(0x42 + affectingRegister) & 0xFF] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS_CanCompare(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x80;
    mem[effectiveAddress++] = 0x44;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x4480] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS_CanCompare(MOS6502_OpCodes_Main opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x02;
    mem[effectiveAddress++] = 0x44;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x4402 + affectingRegister] = memoryValue;

    cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}
