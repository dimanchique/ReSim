#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"
#include "I8086_ImpliedOpTests.h"

class I8086_MOV_Fixture : public I8086_DoubleOpFixture {};
 class I8086_MOV_IM_Fixture : public I8086_SingleOpFixture {};
 class I8086_MOV_IMPL_Fixture : public I8086_ImpliedOpFixture {};

// Mem (BX addressed) <-- AX
TEST_F(I8086_MOV_Fixture, MOV_Ev_Gv_BX_Addressed_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const WORD refValue = cpu.AX;

    TestMemRegInstruction(memAddress, memValue, MOV_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (Direct addressed) <-- BX
TEST_F(I8086_MOV_Fixture, MOV_Ev_Gv_Direct_Addressed_BX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wBX;

    cpu.BX = 0x0060;
    cyclesExpected = 16 + 6;

    const WORD memValue = 0x12C;
    const DWORD memAddress = 0x1000;
    const WORD refValue = cpu.BX;

    TestMemRegInstruction(memAddress, memValue, MOV_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (BP addressed WithDisp) <-- DX
TEST_F(I8086_MOV_Fixture, MOV_Ev_Gv_BP_Addressed_WithDisp_DX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wDX;

    cpu.DX = 0x0060;
    cpu.SS = 0x2000; // BP is force-replacing by SS
    cyclesExpected = 16 + 9;

    const WORD memValue = 0x12C;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);
    const WORD refValue = cpu.DX;

    TestMemRegInstruction(memAddress, memValue, MOV_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (BX SI addressed WithDisp) <-- AX
TEST_F(I8086_MOV_Fixture, MOV_Ev_Gv_BXSI_Addressed_WithDisp_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;
    cyclesExpected = 16 + 11;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);
    const WORD refValue = cpu.AX;

    TestMemRegInstruction(memAddress, memValue, MOV_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (Direct addressed) <-- DS
TEST_F(I8086_MOV_Fixture, MOV_Ew_Sw_Direct_Addressed_DS) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::SReg;
    modReg.rightOp.regData = swDS;

    cyclesExpected = 16 + 6;

    const WORD memValue = 0x12C;
    const DWORD memAddress = 0x1000;

    TestMemRegInstruction(memAddress, memValue, MOV_Ew_Sw, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, cpu.DS);
}

// DS <-- Mem (Direct addressed)
TEST_F(I8086_MOV_Fixture, MOV_Sw_Ew_Direct_Addressed_DS) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::SReg;
    modReg.leftOp.regData = swDS;

    modReg.rightOp.archetype = OperandArchetype::Mem;
    modReg.rightOp.memData.dispSize = 1;
    modReg.rightOp.memData.dispValue = 0xAD;
    modReg.rightOp.memData.mode = modeBXpSI;

    cyclesExpected = 16 + 6;

    cpu.BX = 0x8000;
    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + modReg.rightOp.memData.dispValue;

    TestMemRegInstruction(memAddress, memValue, MOV_Sw_Ew, modReg, 16);

    EXPECT_EQ(cpu.DS, memValue);
}

// AX <-- BX
TEST_F(I8086_MOV_Fixture, MOV_Gv_Ev_AX_BX) {
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.BX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, MOV_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);
}

// BX <-- DI
TEST_F(I8086_MOV_Fixture, MOV_Gv_Ev_BX_DI) {
    cpu.BX = 0x0060;
    cpu.DI = 0x009A;
    const BYTE leftReg = wBX;
    const BYTE rightReg = wDI;
    const WORD refValue = cpu.DI;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, MOV_Gv_Ev, 16);

    EXPECT_EQ(cpu.BX, refValue);
}

// AL <-- BH
TEST_F(I8086_MOV_Fixture, MOV_Gb_Eb_AL_BH) {
    cpu.AL = 0x60;
    cpu.BH = 0x9A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = cpu.BH;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, MOV_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);
}

// BL <-- CL
TEST_F(I8086_MOV_Fixture, MOV_Gb_Eb_BL_CL) {
    cpu.BL = 0x0060;
    cpu.CL = 0x009A;
    const BYTE leftReg = bBL;
    const BYTE rightReg = bCL;
    const BYTE refValue = cpu.CL;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, MOV_Gb_Eb, 16);

    EXPECT_EQ(cpu.BL, refValue);
}

// Mem8 <-- Mem8
TEST_F(I8086_MOV_IMPL_Fixture, MOVSB) {
    cpu.SI = 0x0400;
    cpu.DI = 0x0500;
    cpu.DS = 0x2000;
    cpu.ES = 0x3000;
    cpu.Status.D = 0;

    const DWORD src = EFFECTIVE_ADDRESS(cpu.SI, cpu.DS);
    const DWORD dst = EFFECTIVE_ADDRESS(cpu.DI, cpu.ES);

    const BYTE dataSize = 5;
    BYTE data[dataSize] = {'h', 'e', 'l', 'l', 'o'};
    for (BYTE i = 0; i < dataSize; i++)
        mem[src + i] = data[i];

    for (BYTE i = 0; i < dataSize; i++)
        mem[effectiveAddress++] = MOVSB;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cpu.Run();

    for (BYTE i = 0; i < dataSize; i++)
        EXPECT_EQ(mem[dst + i], data[i]);
}

// Mem8 <-- Mem8
TEST_F(I8086_MOV_IMPL_Fixture, MOVSW) {
    cpu.SI = 0x0400;
    cpu.DI = 0x0500;
    cpu.DS = 0x2000;
    cpu.ES = 0x3000;
    cpu.Status.D = 0;

    const DWORD src = EFFECTIVE_ADDRESS(cpu.SI, cpu.DS);
    const DWORD dst = EFFECTIVE_ADDRESS(cpu.DI, cpu.ES);

    const BYTE dataSize = 6;
    WORD data[dataSize] = {0xDEAD, 0xBEEF, 0xBABE, 0x4B1D, 0x00BA, 0xB10C};
    for (BYTE i = 0; i < dataSize; i++) {
        mem[src + 2*i] = data[i] & 0x0F;
        mem[src + 2*i + 1] = (data[i] >> 8) & 0x0F;
    }

    for (BYTE i = 0; i < dataSize; i++)
        mem[effectiveAddress++] = MOVSW;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cpu.Run();

    for (BYTE i = 0; i < dataSize; i++) {
        EXPECT_EQ(mem[dst + 2*i], data[i] & 0x0F);
        EXPECT_EQ(mem[dst + 2*i + 1], (data[i] >> 8) & 0x0F);
    }
}
