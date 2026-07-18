#include "I8086_TestingSuite.h"

class I8086_JCXZ_Fixture : public I8086_TestFixture{};

TEST_F(I8086_JCXZ_Fixture, JCXZ_JumpTaken) {
    cpu.CX = 0;

    mem[effectiveAddress++] = JCXZ_Jb;
    mem[effectiveAddress++] = 0x10;
    mem[effectiveAddress + 0x10] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();
    EXPECT_EQ(cpu.PC, 0x1012);
}

TEST_F(I8086_JCXZ_Fixture, JCXZ_JumpNotTaken) {
    cpu.CX = 0x0001;

    mem[effectiveAddress++] = JCXZ_Jb;
    mem[effectiveAddress++] = 0x10;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();
    EXPECT_EQ(cpu.PC, 0x1002);
}

TEST_F(I8086_JCXZ_Fixture, JCXZ_JumpBackwards) {
    cpu.CX = 0;

    mem[effectiveAddress++] = JCXZ_Jb;
    mem[effectiveAddress++] = 0xFD; // -3 → target PC = 0x0FFF
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    mem[EFFECTIVE_ADDRESS(0x0FFF, cpu.CS)] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();
    EXPECT_EQ(cpu.PC, 0x0FFF);
}
