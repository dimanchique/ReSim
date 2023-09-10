#include "CPU6502_TestingSuite.h"

class CPU6502_CLFixture : public CPU6502_TestFixture {
public:
    void CL_CanClearFlag(CPU6502_OpCodes OpCode, BYTE StatusFlag) {
        cpu.Status.SetFlag(StatusFlag);
        mem[0xFFFC] = OpCode;

        const U32 NumCycles = 2;

        // when:
        U32 CNT = cpu.Run(NumCycles, mem);

        // then:
        EXPECT_FALSE(cpu.Status & StatusFlag);
        EXPECT_EQ(CNT, NumCycles);
    }
};

TEST_F(CPU6502_CLFixture, CLC_IMPL_CanSetCarryFlag){
    CL_CanClearFlag(CLC_IMPL, CPU6502_Status_C);
}

TEST_F(CPU6502_CLFixture, CLD_IMPL_CanSetCarryFlag){
    CL_CanClearFlag(CLD_IMPL, CPU6502_Status_D);
}

TEST_F(CPU6502_CLFixture, CLI_IMPL_CanSetCarryFlag){
    CL_CanClearFlag(CLI_IMPL, CPU6502_Status_I);
}

TEST_F(CPU6502_CLFixture, CLV_IMPL_CanSetCarryFlag){
    CL_CanClearFlag(CLV_IMPL, CPU6502_Status_V);
}