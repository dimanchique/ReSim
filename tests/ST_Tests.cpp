#include "CPU6502_ST_Tests.h"

void CPU6502_STFixture::ST_ZP_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister){
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x80;
    mem[0x0080] = 0x00;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x0080], sourceRegister);
    CheckCyclesCount();
}

void CPU6502_STFixture::ST_ZP_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE affectingRegister){
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x80;
    BYTE TargetAddress = (mem[0xFFFD] + affectingRegister) & 0xFF;
    mem[TargetAddress] = 0x00;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[TargetAddress], sourceRegister);
    CheckCyclesCount();
}

void CPU6502_STFixture::ST_ABS_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister){
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x80;
    mem[0x8000] = 0x00;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x8000], sourceRegister);
    CheckCyclesCount();
}

void CPU6502_STFixture::ST_ABS_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE affectingRegister){
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x80;
    WORD TargetAddress = 0x8000 + affectingRegister;
    mem[TargetAddress] = 0x00;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[TargetAddress], sourceRegister);
    CheckCyclesCount();
}