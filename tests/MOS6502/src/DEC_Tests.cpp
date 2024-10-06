#include "MOS6502_DEC_Tests.h"

void MOS6502_DECFixture::DEC_ZP_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x42;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x42 + offsetValueRegister] = memoryValue;
    BYTE targetValue = memoryValue - 1;

    cyclesExpected = offsetValueRegister ? 6 : 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[0x42 + offsetValueRegister], memoryValue);
    EXPECT_EQ(mem[0x42 + offsetValueRegister], targetValue);
    CheckCyclesCount();
}

void MOS6502_DECFixture::DEC_ABS_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    BYTE targetValue = memoryValue - 1;
    WORD targetAddress = 0x4200;
    WORD displacedAddress = targetAddress + offsetValueRegister;

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = targetAddress & 0xFF;
    mem[0xFF02] = (targetAddress >> 8) & 0xFF;
    mem[0xFF03] = STOP_OPCODE;
    mem[displacedAddress] = memoryValue;

    cyclesExpected = opcode == DEC_ABSX ? 7 : 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[displacedAddress], memoryValue);
    EXPECT_EQ(mem[displacedAddress], targetValue);
    CheckCyclesCount();
}

void MOS6502_DECFixture::DEC_IMPL_CanAffectValue(MOS6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    BYTE initialValue = targetRegister;
    BYTE targetValue = initialValue - 1;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = STOP_OPCODE;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(targetRegister, initialValue);
    EXPECT_EQ(targetRegister, targetValue);
    CheckCyclesCount();
}
