#include "I8086_TestingSuite.h"
#include "I8086_SingleOpTests.h"

class I8086_MOV_Ix_Fixture : public I8086_TestFixture {
  public:
    template<typename T>
    void TestMovImmediateData(T* regPtr, const BYTE opCode) {
        // given:
        *regPtr = 0;
        const T immValue = std::is_same_v<T, WORD> ? 0xBABE : 0xBE;
        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = immValue & 0xFF;
        if (std::is_same_v<T, WORD>)
            mem[effectiveAddress++] = (immValue >> 8) & 0xFF;
        mem[effectiveAddress] = I8086_STOP_OPCODE;
        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(*regPtr, immValue);
    }
};

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Al) {
    TestMovImmediateData(&cpu.AL, MOV_AL_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Ah) {
    TestMovImmediateData(&cpu.AH, MOV_AH_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Bl) {
    TestMovImmediateData(&cpu.BL, MOV_BL_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Bh) {
    TestMovImmediateData(&cpu.BH, MOV_BH_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Cl) {
    TestMovImmediateData(&cpu.CL, MOV_CL_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Ch) {
    TestMovImmediateData(&cpu.CH, MOV_CH_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Dl) {
    TestMovImmediateData(&cpu.DL, MOV_DL_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_Dh) {
    TestMovImmediateData(&cpu.DH, MOV_DH_Ib);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_AX) {
    TestMovImmediateData(&cpu.AX, MOV_AX_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_BX) {
    TestMovImmediateData(&cpu.BX, MOV_BX_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_CX) {
    TestMovImmediateData(&cpu.CX, MOV_CX_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_DX) {
    TestMovImmediateData(&cpu.DX, MOV_DX_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_BP) {
    TestMovImmediateData(&cpu.BP, MOV_BP_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_SP) {
    TestMovImmediateData(&cpu.SP, MOV_SP_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_SI) {
    TestMovImmediateData(&cpu.SI, MOV_SI_Iv);
}

TEST_F(I8086_MOV_Ix_Fixture, MOV_Im_DI) {
    TestMovImmediateData(&cpu.DI, MOV_DI_Iv);
}

class I8086_MOV_Ex_Ix_Fixture : public I8086_SingleOpFixture {};

TEST_F(I8086_MOV_Ex_Ix_Fixture, MOV_AX_Iv) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Reg;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    WORD initialValue = 0x60;
    cpu.AX = initialValue;

    cyclesExpected = 16 + 5;

    const WORD memValue = 0xCCDA;

    TestImmediateInstruction<WORD>(MOV_Ev_Iv, modReg, memValue, 16);

    EXPECT_EQ(cpu.AX, memValue);
}

TEST_F(I8086_MOV_Ex_Ix_Fixture, MOV_DX_Iv) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Reg;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wDX;

    WORD initialValue = 0x60;
    cpu.DX = initialValue;

    cyclesExpected = 16 + 5;

    const WORD memValue = 0xCCDA;

    TestImmediateInstruction<WORD>(MOV_Ev_Iv, modReg, memValue, 16);

    EXPECT_EQ(cpu.DX, memValue);
}
