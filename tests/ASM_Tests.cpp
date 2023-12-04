#include "CPU6502_ASMTestingSuite.h"

class CPU6502_ASMFixture : public CPU6502_ASMTestFixture {};

TEST_F(CPU6502_ASMFixture, CRC32_ComputeTest) {
    // given:
    SetExecutable("../tools/asm_tests/CRC32_test.bin", mem, 0x3000);

    for(auto i = 0x1000; i < 0x1100; i++)
        mem[i] = 0x02;

    // when:
    RunTest();

    // then:
    EXPECT_EQ(mem[0x06], 0x64);
    EXPECT_EQ(mem[0x07], 0x80);
    EXPECT_EQ(mem[0x08], 0xDE);
    EXPECT_EQ(mem[0x09], 0xD4);
}

TEST_F(CPU6502_ASMFixture, CRC16_ComputeTest) {
    // given:
    SetExecutable("../tools/asm_tests/CRC16_test.bin", mem, 0x3000);

    for(auto i = 0x1000; i < 0x1100; i++)
        mem[i] = 0x02;

    // when:
    RunTest();

    // then:
    EXPECT_EQ(mem[0x06], 0xA1);
    EXPECT_EQ(mem[0x07], 0xF1);
}
