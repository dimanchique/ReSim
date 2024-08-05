#include "MOS6502_INC_Tests.h"

void MOS6502_INCFixture::INC_ZP_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x42;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x42 + offsetValueRegister] = memoryValue;
    BYTE targetValue = memoryValue + 1;

    cyclesExpected = offsetValueRegister ? 6 : 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[0x42 + offsetValueRegister], memoryValue);
    EXPECT_EQ(mem[0x42 + offsetValueRegister], targetValue);
    CheckCyclesCount();
}

void MOS6502_INCFixture::INC_ABS_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x42;
    mem[0xFF03] = STOP_OPCODE;
    mem[0x4200 + offsetValueRegister] = memoryValue;
    BYTE targetValue = memoryValue + 1;

    cyclesExpected = offsetValueRegister ? 7 : 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[0x4200 + offsetValueRegister], memoryValue);
    EXPECT_EQ(mem[0x4200 + offsetValueRegister], targetValue);
    CheckCyclesCount();
}

void MOS6502_INCFixture::INC_IMPL_CanAffectValue(MOS6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    BYTE initialValue = targetRegister;
    BYTE targetValue = initialValue + 1;
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
