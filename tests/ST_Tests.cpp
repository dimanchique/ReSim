#include "CPU6502_ST_Tests.h"

void CPU6502_STFixture::ST_ZP_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister){
    //given:
    SourceRegister = 0x2F;
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x80;
    mem[0x0080] = 0x00;

    //when:
    const U32 NumCycles = 3;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(mem[0x0080], SourceRegister);
    EXPECT_EQ(CNT, NumCycles);
}

void CPU6502_STFixture::ST_ZP_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE AffectingRegister){
    //given:
    SourceRegister = 0x2F;
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x80;
    BYTE TargetAddress = (mem[0xFFFD] + AffectingRegister) & 0xFF;
    mem[TargetAddress] = 0x00;

    //when:
    const U32 NumCycles = 4;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(mem[TargetAddress], SourceRegister);
    EXPECT_EQ(CNT, NumCycles);
}

void CPU6502_STFixture::ST_ABS_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister){
    //given:
    SourceRegister = 0x2F;
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x80;
    mem[0x8000] = 0x00;

    //when:
    const U32 NumCycles = 4;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(mem[0x8000], SourceRegister);
    EXPECT_EQ(CNT, NumCycles);
}

void CPU6502_STFixture::ST_ABS_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE AffectingRegister){
    //given:
    SourceRegister = 0x2F;
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = 0x00;
    mem[0xFFFE] = 0x80;
    WORD TargetAddress = 0x8000 + AffectingRegister;
    mem[TargetAddress] = 0x00;

    //when:
    const U32 NumCycles = 5;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(mem[TargetAddress], SourceRegister);
    EXPECT_EQ(CNT, NumCycles);
}