#include "I8080_ASMTestingSuite.h"
#include <filesystem>

class I8080_ASMFixture : public I8080_ASMTestFixture {};

TEST_F(I8080_ASMFixture, MULT_ComputeTest) {
    // given:
    SetExecutable("mult.bin");
    cpu.A = 0x12;
    cpu.D = 0x07;
    WORD expectedValue = cpu.A * cpu.D;
    assert(cpu.A * cpu.D < 0xFF);

    RunTest();

    // then:
    EXPECT_EQ(mem[0101], expectedValue);
}

TEST_F(I8080_ASMFixture, ADD_ComputeTest) {
    // given:
    SetExecutable("add.bin");
    // testing 5 + 8, result is stored in 0o202 (octal)

    RunTest();

    // then:
    EXPECT_EQ(mem[0202], 5 + 8);
}
