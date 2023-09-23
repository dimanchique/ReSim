#include "CPU6502_LD_Tests.h"

void CPU6502_LDFixture::LD_IM_CanLoadValue(CPU6502_OpCodes opcode, BYTE& targetRegister){
    // given:
    BYTE OldValue = 0x44;
    BYTE NewValue = 0x04;
    targetRegister = OldValue;
    mem[0xFFFC] = opcode;                                       // read value from the next mem cell
    mem[0xFFFD] = NewValue;                                     // store this value in target register

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(targetRegister, OldValue);
    EXPECT_EQ(targetRegister, NewValue);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_IM_CanAffectZeroFlag(CPU6502_OpCodes opcode){
    // given:
    mem[0xFFFC] = opcode;                                       // read value from the next mem cell
    mem[0xFFFD] = 0x0;                                          // store this value in target register

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes opcode){
    // given:
    mem[0xFFFC] = opcode;                                       // read value from the next mem cell
    mem[0xFFFD] = 0x80;                                         // store this value in target register

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE& targetRegister){
    // given:
    mem[0xFFFC] = opcode;                                       // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
    mem[0x0042] = 0x37;                                         // store this value in target register

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE& targetRegister, BYTE affectingRegister){
    // given:
    mem[0xFFFC] = opcode;                                       // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                                         // add affectingRegister value to this pointer
    mem[(mem[0xFFFD] + affectingRegister) & 0xFF] = 0x37;       // read value from memory using pointer
                                                                // store this value in targetRegister register
    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE& targetRegister){
    // given:
    mem[0xFFFC] = opcode;                       // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480
    mem[0x4480] = 0x37;                         // store this value in targetRegister

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

void CPU6502_LDFixture::LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE& targetRegister, BYTE affectingRegister){
    // given:
    mem[0xFFFC] = opcode;                       // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x02;                         // read from this address
    mem[0xFFFE] = 0x44;                         // target value is in memory address 0x4402 + affectingRegister
    mem[0x4402 + affectingRegister] = 0x37;     // store this value in targetRegister

    cyclesExpected = CPU6502::isPageCrossed(0x4402 + affectingRegister, 0x4402 ) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(targetRegister, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
