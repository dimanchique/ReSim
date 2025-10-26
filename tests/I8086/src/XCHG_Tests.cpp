#include "I8086_DoubleOpTests.h"
#include "I8086_ImpliedOpTests.h"

class I8086_XCHG_AX_Fixture : public I8086_ImpliedOpTests {
public:
    void TestXCHG_AX(I8086_OpCodes_Main opCode, WORD *regPtr) {
        constexpr WORD tmp1 = 0xBABE;
        constexpr WORD tmp2 = 0xDEAD;
        cpu.AX = tmp1;
        *regPtr = tmp2;
        TestImpliedInstruction(opCode);
        EXPECT_EQ(cpu.AX, tmp2);
        EXPECT_EQ(*regPtr, tmp1);
    }
};

TEST_F(I8086_XCHG_AX_Fixture, XCHG_CX_AX) {
    TestXCHG_AX(XCHG_CX_AX, &cpu.CX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_DX_AX) {
    TestXCHG_AX(XCHG_DX_AX, &cpu.DX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_BX_AX) {
    TestXCHG_AX(XCHG_BX_AX, &cpu.BX);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_SP_AX) {
    TestXCHG_AX(XCHG_SP_AX, &cpu.SP);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_BP_AX) {
    TestXCHG_AX(XCHG_BP_AX, &cpu.BP);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_SI_AX) {
    TestXCHG_AX(XCHG_SI_AX, &cpu.SI);
}

TEST_F(I8086_XCHG_AX_Fixture, XCHG_DI_AX) {
    TestXCHG_AX(XCHG_DI_AX, &cpu.DI);
}

class I8086_XCHG_Fixture : public I8086_DoubleOpFixture {};

TEST_F(I8086_XCHG_Fixture, XCHG_Gv_Ev_AX_BX) {
    constexpr WORD value1 = 0x0060;
    constexpr WORD value2 = 0x009A;
    cpu.AX = value1;
    cpu.BX = value2;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, XCHG_Gv_Ev, 16);
    EXPECT_EQ(cpu.AX, value2);
    EXPECT_EQ(cpu.BX, value1);
}

TEST_F(I8086_XCHG_Fixture, XCHG_Gb_Eb_BL_BX) {
    constexpr WORD value1 = 0x0060;
    constexpr WORD value2 = 0x009A;
    cpu.BL = value1;
    cpu.DL = value2;
    const BYTE leftReg = bBL;
    const BYTE rightReg = bDL;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, XCHG_Gb_Eb, 16);
    EXPECT_EQ(cpu.BL, value2);
    EXPECT_EQ(cpu.DL, value1);
}

TEST_F(I8086_XCHG_Fixture, XCHG_Gv_Ev_BX_Addressed_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = bDH;

    const BYTE refValue = 0xFA;
    const BYTE memValue = 0xBE;

    cpu.DH = refValue;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    TestMemRegInstruction(memAddress, memValue, XCHG_Gb_Eb, modReg, 16);

    WORD result = mem[memAddress];
    EXPECT_EQ(result, refValue);
    EXPECT_EQ(cpu.DH, memValue);
}

TEST_F(I8086_XCHG_Fixture, OR_Gv_Ev_BXSI_Addressed_WithDisp_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    const WORD refValue = 0xFACE;
    const WORD memValue = 0xBABE;

    cpu.AX = refValue;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;
    cyclesExpected = 16 + 11;

    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);
    TestMemRegInstruction(memAddress, memValue, XCHG_Gv_Ev, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
    EXPECT_EQ(cpu.AX, memValue);
}
