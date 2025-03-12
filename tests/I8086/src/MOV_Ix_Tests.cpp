#include "I8086_TestingSuite.h"

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
        mem[effectiveAddress] = STOP_OPCODE;
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
