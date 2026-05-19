#include "I8086_ImpliedOpTests.h"

class I8086_ST_CL_CM_Fixture : public I8086_ImpliedOpFixture {
public:
    void ST_CanSetFlag(I8086_OpCodes_Main opCode, const WORD statusFieldMask) {
        // given:
        cpu.Status.Value &= ~statusFieldMask;

        // when:
        TestImpliedInstruction(opCode);

        // then:
        EXPECT_EQ(cpu.Status.Value & statusFieldMask, statusFieldMask);
    }

    void CL_CanClearFlag(I8086_OpCodes_Main opCode, const WORD statusFieldMask) {
        // given:
        cpu.Status.Value |= statusFieldMask;

        // when:
        TestImpliedInstruction(opCode);

        // then:
        EXPECT_EQ(cpu.Status.Value & statusFieldMask, 0);
    }

    void CM_CanComplimentCarry(bool initialCarry) {
        // given:
        cpu.Status.C = initialCarry;

        // when:
        TestImpliedInstruction(CMC);

        // then:
        EXPECT_EQ(cpu.Status.C, !initialCarry);
    }
};

TEST_F(I8086_ST_CL_CM_Fixture, STC_CanSetCarry) {
    ST_CanSetFlag(STC, I8086_Status_C);
}

TEST_F(I8086_ST_CL_CM_Fixture, STD_CanSetDirection) {
    ST_CanSetFlag(STD, I8086_Status_D);
}

TEST_F(I8086_ST_CL_CM_Fixture, STI_CanSetInterrupt) {
    ST_CanSetFlag(STI, I8086_Status_I);
}

TEST_F(I8086_ST_CL_CM_Fixture, CLC_CanClearCarry) {
    CL_CanClearFlag(CLC, I8086_Status_C);
}

TEST_F(I8086_ST_CL_CM_Fixture, CLD_CanClearDirection) {
    CL_CanClearFlag(CLD, I8086_Status_D);
}

TEST_F(I8086_ST_CL_CM_Fixture, CL_CanClearInterrupt) {
    CL_CanClearFlag(CLI, I8086_Status_I);
}

TEST_F(I8086_ST_CL_CM_Fixture, CM_CanComplementCarry_1) {
    CM_CanComplimentCarry(true);
}

TEST_F(I8086_ST_CL_CM_Fixture, CM_CanComplementCarry_2) {
    CM_CanComplimentCarry(false);
}
