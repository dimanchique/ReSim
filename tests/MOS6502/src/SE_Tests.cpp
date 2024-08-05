#include "MOS6502_TestingSuite.h"

class MOS6502_SEFixture : public MOS6502_TestFixture {
public:
    void SE_CanSetFlag(MOS6502_OpCodes opcode, BYTE statusFlag) {
        // given:
        cpu.Status.SetStatusFlagValue(statusFlag, false);
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0xFF;
        mem[0xFF00] = opcode;
        mem[0xFF01] = STOP_OPCODE;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_TRUE(cpu.Status.GetStatusValue(statusFlag));
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_SEFixture, SEC_IMPL_CanSetCarryFlag) {
    SE_CanSetFlag(SEC_IMPL, MOS6502_Status_C);
}

TEST_F(MOS6502_SEFixture, SED_IMPL_CanSetDecimalFlag) {
    SE_CanSetFlag(SED_IMPL, MOS6502_Status_D);
}

TEST_F(MOS6502_SEFixture, SEI_IMPL_CanSetInterruptFlag) {
    SE_CanSetFlag(SEI_IMPL, MOS6502_Status_I);
}