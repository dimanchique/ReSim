#include "I8086_TestingSuite.h"
#include "I8086_OpCodes_Groups.h"

TEST_F(I8086_TestFixture, LOOP_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123;

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = LOOP_Jb;
    mem[memoryAddress++] = 0xFC; // PC offset = -0x0004
    mem[memoryAddress++] = 0xFF; //
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1111);
}

TEST_F(I8086_TestFixture, LOOPZ_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123;

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = TEST_AL_Ib;
    mem[memoryAddress++] = 0;   // Just to get Z=1
    mem[memoryAddress++] = LOOP_Jb;
    mem[memoryAddress++] = 0xFA; // PC offset = -0x0006
    mem[memoryAddress++] = 0xFF; //
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1111);
}

TEST_F(I8086_TestFixture, LOOPNZ_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123;

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = TEST_AL_Ib;
    mem[memoryAddress++] = 0xFF; // Just to get Z=0
    mem[memoryAddress++] = LOOP_Jb;
    mem[memoryAddress++] = 0xFA; // PC offset = -0x0006
    mem[memoryAddress++] = 0xFF; //
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1111);
}
