#include "CPU6502_Tests.h"

class CPU6502_JSRFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanJump) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    const U32 NumCycles = 6;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x4242);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanExecuteNextOpCode) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;

    const U32 NumCycles = 8;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);                 // 0x84 is 0b10000100 and N is checking the 7's bit in A and it's 1
    EXPECT_EQ(CNT, NumCycles);
}
