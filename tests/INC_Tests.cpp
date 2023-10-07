#include "CPU6502_INC_Tests.h"

void CPU6502_INCFixture::INC_ZP_CanAffectValue(CPU6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x42;
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

void CPU6502_INCFixture::INC_ABS_CanAffectValue(CPU6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister) {
    // given:
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x42;
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

void CPU6502_INCFixture::INC_IMPL_CanAffectValue(CPU6502_OpCodes opcode, BYTE &targetRegister) {
    // given:
    BYTE initialValue = targetRegister;
    BYTE targetValue = initialValue + 1;
    mem[0xFFFC] = opcode;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(targetRegister, initialValue);
    EXPECT_EQ(targetRegister, targetValue);
    CheckCyclesCount();
}
