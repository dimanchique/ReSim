#include "I8086_TestingSuite.h"
#include "I8086_OpCodes_Groups.h"

class I8086_LOOP_Fixture : public I8086_TestFixture{};

TEST_F(I8086_LOOP_Fixture, LOOP_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123;

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = LOOP_Jb;
    mem[memoryAddress++] = 0xFD; // PC offset = -0x0003
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1111);
}

TEST_F(I8086_LOOP_Fixture, LOOPZ_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123;

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = TEST_AL_Ib;
    mem[memoryAddress++] = 0;   // Just to get Z=1
    mem[memoryAddress++] = LOOPZ_Jb;
    mem[memoryAddress++] = 0xFB; // PC offset = -0x0005
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1111);
}

TEST_F(I8086_LOOP_Fixture, LOOPNZ_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.AX = 0x1234;
    cpu.CX = 0x0123; // we want to iterate 0x0123 times

    DWORD memoryAddress = 0x11000;

    mem[memoryAddress++] = DEC_AX;
    mem[memoryAddress++] = TEST_AL_Ib;
    mem[memoryAddress++] = 0xFF; // Just to get Z=0
    mem[memoryAddress++] = LOOPNZ_Jb;
    mem[memoryAddress++] = 0xFB; // PC offset = -0x0005
    mem[memoryAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, 0x1200); // but AL is hits 00 earlier, at 0x1200 value
}
