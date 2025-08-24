#include "MOS6502_TestingSuite.h"

class MOS6502_CLFixture : public MOS6502_TestFixture {
public:
    void CL_CanClearFlag(MOS6502_OpCodes_Main opcode, BYTE statusFlag) {
        // given:
        SetStatusBitByMask(statusFlag, true);
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = opcode;
        mem[0xFF01] = STOP_OPCODE;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_FALSE(cpu.Status.Value & statusFlag);
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_CLFixture, CLC_IMPL_CanClearCarryFlag) {
    CL_CanClearFlag(CLC_IMPL, MOS6502_Status_C);
}

TEST_F(MOS6502_CLFixture, CLD_IMPL_CanClearDecimalFlag) {
    CL_CanClearFlag(CLD_IMPL, MOS6502_Status_D);
}

TEST_F(MOS6502_CLFixture, CLI_IMPL_CanClearInterruptFlag) {
    CL_CanClearFlag(CLI_IMPL, MOS6502_Status_I);
}

TEST_F(MOS6502_CLFixture, CLV_IMPL_CanClearCOverflowFlag) {
    CL_CanClearFlag(CLV_IMPL, MOS6502_Status_V);
}
