#include "CPU6502_INC_Tests.h"

void CPU6502_INCFixture::INC_ZP_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister){
    // given:
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x42;
    mem[0x42 + OffsetValueRegister] = MemoryValue;
    BYTE TargetValue = MemoryValue + 1;

    CyclesExpected = OffsetValueRegister ? 6 : 5;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[0x42 + OffsetValueRegister], MemoryValue);
    EXPECT_EQ(mem[0x42 + OffsetValueRegister], TargetValue);
    CheckCyclesCount();
}

void CPU6502_INCFixture::INC_ABS_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister){
    // given:
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x42;
    mem[0x4200 + OffsetValueRegister] = MemoryValue;
    BYTE TargetValue = MemoryValue + 1;

    CyclesExpected = OffsetValueRegister ? 7 : 6;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(mem[0x4200 + OffsetValueRegister], MemoryValue);
    EXPECT_EQ(mem[0x4200 + OffsetValueRegister], TargetValue);
    CheckCyclesCount();
}

void CPU6502_INCFixture::INC_IMPL_CanAffectValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister){
    // given:
    BYTE InitialValue = TargetRegister;
    BYTE TargetValue = InitialValue + 1;
    mem[0xFFFC] = OpCode;

    CyclesExpected = 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(TargetRegister, InitialValue);
    EXPECT_EQ(TargetRegister, TargetValue);
    CheckCyclesCount();
}
