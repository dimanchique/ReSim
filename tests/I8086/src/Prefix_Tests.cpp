#include "I8086_TestingSuite.h"

class I8086_Prefix_Fixture : public I8086_TestFixture {};

// -------------------------------------------------------------------
// Sanity — MOV [BX], AX without prefix (uses DS by default)
// -------------------------------------------------------------------

TEST_F(I8086_Prefix_Fixture, MOV_BX_AX_NoPrefix) {
    cpu.AX = 0x1234;
    cpu.BX = 0x0050;
    cpu.DS = 0x2000;

    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD dsAddr = EFFECTIVE_ADDRESS(0x0050, 0x2000);
    EXPECT_EQ(cpu.Read<WORD>(dsAddr), 0x1234);
}

// -------------------------------------------------------------------
// Segment-override prefixes
// -------------------------------------------------------------------

TEST_F(I8086_Prefix_Fixture, ES_SegmentOverride_MOV_BX_AX) {
    cpu.AX = 0x1234;
    cpu.BX = 0x0050;
    cpu.DS = 0x2000;
    cpu.ES = 0x3000;

    // ES prefix + MOV [BX], AX (0x89 0x07)
    mem[effectiveAddress++] = ES;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD dsAddr = EFFECTIVE_ADDRESS(0x0050, 0x2000);
    const DWORD esAddr = EFFECTIVE_ADDRESS(0x0050, 0x3000);

    // MOV with ES prefix writes to ES:BX, NOT DS:BX
    EXPECT_EQ(cpu.Read<WORD>(esAddr), 0x1234);
    EXPECT_NE(cpu.Read<WORD>(dsAddr), 0x1234);
}

TEST_F(I8086_Prefix_Fixture, CS_SegmentOverride_MOV_BX_AX) {
    cpu.AX = 0x5678;
    cpu.BX = 0x0060;
    cpu.DS = 0x2000;
    cpu.CS = 0x1000;

    mem[effectiveAddress++] = CS;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD csAddr = EFFECTIVE_ADDRESS(0x0060, 0x1000);
    EXPECT_EQ(cpu.Read<WORD>(csAddr), 0x5678);
}

TEST_F(I8086_Prefix_Fixture, SS_SegmentOverride_MOV_BX_AX) {
    cpu.AX = 0x9ABC;
    cpu.BX = 0x0070;
    cpu.DS = 0x2000;
    cpu.SS = 0x4000;

    mem[effectiveAddress++] = SS;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD ssAddr = EFFECTIVE_ADDRESS(0x0070, 0x4000);
    EXPECT_EQ(cpu.Read<WORD>(ssAddr), 0x9ABC);
}

TEST_F(I8086_Prefix_Fixture, DS_SegmentOverride_MOV_BX_AX) {
    cpu.AX = 0xDEAD;
    cpu.BX = 0x0080;
    cpu.DS = 0x2000;

    mem[effectiveAddress++] = DS;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD dsAddr = EFFECTIVE_ADDRESS(0x0080, 0x2000);
    EXPECT_EQ(cpu.Read<WORD>(dsAddr), 0xDEAD);
}

TEST_F(I8086_Prefix_Fixture, LastPrefixWins) {
    cpu.AX = 0xABCD;
    cpu.BX = 0x0090;
    cpu.DS = 0x2000;
    cpu.ES = 0x3000;

    // ES prefix followed by DS prefix → DS should win
    mem[effectiveAddress++] = ES;
    mem[effectiveAddress++] = DS;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x07;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD dsAddr = EFFECTIVE_ADDRESS(0x0090, 0x2000);
    EXPECT_EQ(cpu.Read<WORD>(dsAddr), 0xABCD);
}

TEST_F(I8086_Prefix_Fixture, SegmentOverrideRevertsAfterOneInstruction) {
    cpu.DX = 0x5555;
    cpu.CX = 0xAAAA;
    cpu.BX = 0x00A0;
    cpu.DS = 0x2000;
    cpu.ES = 0x3000;

    // ES-prefixed MOV [BX], DX writes to ES:BX
    mem[effectiveAddress++] = ES;
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x17;         // MOV [BX], DX
    // Next MOV [BX], CX without prefix → should use DS
    mem[effectiveAddress++] = 0x89;
    mem[effectiveAddress++] = 0x0F;         // MOV [BX], CX
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    const DWORD esAddr = EFFECTIVE_ADDRESS(0x00A0, 0x3000);
    const DWORD dsAddr = EFFECTIVE_ADDRESS(0x00A0, 0x2000);

    // First instruction (ES-prefixed) → went to ES
    EXPECT_EQ(cpu.Read<WORD>(esAddr), 0x5555);
    // Second instruction (no prefix) → went to DS
    EXPECT_EQ(cpu.Read<WORD>(dsAddr), 0xAAAA);
}
