#include "MOS6502_DEC_Tests.h"

void MOS6502_DECFixture::DEC_ZP_CanAffectValue(MOS6502_OpCodes_Main opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x42 + offsetValueRegister] = memoryValue;
    BYTE targetValue = memoryValue - 1;

    cyclesExpected = offsetValueRegister ? 6 : 5;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_NE(mem[0x42 + offsetValueRegister], memoryValue);
    EXPECT_EQ(mem[0x42 + offsetValueRegister], targetValue);
    CheckCyclesCount();
}

void MOS6502_DECFixture::DEC_ABS_CanAffectValue(MOS6502_OpCodes_Main opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    BYTE targetValue = memoryValue - 1;
    WORD targetAddress = 0x4200;
    WORD displacedAddress = targetAddress + offsetValueRegister;

    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = targetAddress & 0xFF;
    mem[effectiveAddress++] = (targetAddress >> 8) & 0xFF;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[displacedAddress] = memoryValue;

    cyclesExpected = opcode == DEC_ABSX ? 7 : 6;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_NE(mem[displacedAddress], memoryValue);
    EXPECT_EQ(mem[displacedAddress], targetValue);
    CheckCyclesCount();
}

void MOS6502_DECFixture::DEC_IMPL_CanAffectValue(MOS6502_OpCodes_Main opcode, BYTE &targetRegister) {
    // given:
    BYTE initialValue = targetRegister;
    BYTE targetValue = initialValue - 1;
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_NE(targetRegister, initialValue);
    EXPECT_EQ(targetRegister, targetValue);
    CheckCyclesCount();
}
