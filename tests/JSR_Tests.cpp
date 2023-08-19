#include "CPU6502_Tests.h"

class CPU6502_JSRFixture : public CPU6502_TestFixture{
};

TEST_F(CPU6502_JSRFixture, LDA_IM_WITH_JSR) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;

    // when:
    U32 CNT = cpu.Run(8, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);                 // 0x84 is 0b10000100 and N is checking the 7's bit in A and it's 1
    EXPECT_EQ(CNT, 8);
}
