#include "MOS6502_CM_Tests.h"

void MOS6502_CMFixture::CM_IM_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = memoryValue;
    mem[0xFF02] = STOP_OPCODE;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x42;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x0042] = memoryValue;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x42;
    mem[0xFF02] = STOP_OPCODE;
    mem[(mem[0xFF01] + affectingRegister) & 0xFF] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x80;
    mem[0xFF02] = 0x44;
    mem[0xFF03] = STOP_OPCODE;
    mem[0x4480] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
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
    CheckCyclesCount();
}
