#include "MOS6502_TestingSuite.h"

class MOS6502_CLFixture : public MOS6502_TestFixture {
public:
    void CL_CanClearFlag(MOS6502_OpCodes opcode, BYTE statusFlag) {
        // given:
        cpu.Status.SetStatusFlagValue(statusFlag, true);
        mem[0xFFFC] = opcode;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_FALSE(cpu.Status.GetStatusValue(statusFlag));
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_CLFixture, CLC_IMPL_CanSetCarryFlag) {
    CL_CanClearFlag(CLC_IMPL, MOS6502_Status_C);
}

TEST_F(MOS6502_CLFixture, CLD_IMPL_CanSetCarryFlag) {
    CL_CanClearFlag(CLD_IMPL, MOS6502_Status_D);
}

TEST_F(MOS6502_CLFixture, CLI_IMPL_CanSetCarryFlag) {
    CL_CanClearFlag(CLI_IMPL, MOS6502_Status_I);
}

TEST_F(MOS6502_CLFixture, CLV_IMPL_CanSetCarryFlag) {
    CL_CanClearFlag(CLV_IMPL, MOS6502_Status_V);
}