#include "MOS6502_ST_Tests.h"

void MOS6502_STFixture::ST_ZP_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister) {
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x80;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x0080] = 0x00;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x0080], sourceRegister);
    CheckCyclesCount();
}

void MOS6502_STFixture::ST_ZP_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE affectingRegister) {
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x80;
    mem[0xFF02] = STOP_OPCODE;
    BYTE TargetAddress = (mem[0xFF01] + affectingRegister) & 0xFF;
    mem[TargetAddress] = 0x00;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[TargetAddress], sourceRegister);
    CheckCyclesCount();
}

void MOS6502_STFixture::ST_ABS_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister) {
    //given:
    sourceRegister = 0x2F;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0xFF03] = STOP_OPCODE;
    mem[0x8000] = 0x00;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x8000], sourceRegister);
    CheckCyclesCount();
}

void MOS6502_STFixture::ST_ABS_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE affectingRegister) {
    //given:
    WORD targetAddress = 0x8000;
    WORD displacedAddress = targetAddress + affectingRegister;

    sourceRegister = 0x2F;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = opcode;
    mem[0xFF01] = targetAddress & 0xFF;
    mem[0xFF02] = (targetAddress >> 8) & 0xFF;
    mem[0xFF03] = STOP_OPCODE;
    mem[displacedAddress] = 0x00;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[displacedAddress], sourceRegister);
    CheckCyclesCount();
}