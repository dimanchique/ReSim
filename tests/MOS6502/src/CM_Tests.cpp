#include "MOS6502_CM_Tests.h"

void MOS6502_CMFixture::CM_IM(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = memoryValue;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = memoryValue;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ZP(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x42;
    mem[(mem[0xFFFD] + affectingRegister) & 0xFF] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x80;
    mem[0xFFFE] = 0x44;
    mem[0x4480] = memoryValue;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

void MOS6502_CMFixture::CM_ABS(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister) {
    // given:
    targetRegister = initialValue;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + affectingRegister] = memoryValue;

    cyclesExpected = IsPageCrossed(0x4402 + affectingRegister, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}
