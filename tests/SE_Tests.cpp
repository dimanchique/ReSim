#include "CPU6502_TestingSuite.h"

class CPU6502_SEFixture : public CPU6502_TestFixture {
public:
    void SE_CanSetFlag(CPU6502_OpCodes OpCode, BYTE StatusFlag) {
        cpu.Status.ClearFlag(StatusFlag);
        mem[0xFFFC] = OpCode;

        CyclesExpected = 2;

        // when:
        CyclesPassed = cpu.Run(CyclesExpected, mem);

        // then:
        EXPECT_TRUE(cpu.Status.GetStatusValue(StatusFlag));
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_SEFixture, SEC_IMPL_CanSetCarryFlag){
    SE_CanSetFlag(SEC_IMPL, CPU6502_Status_C);
}

TEST_F(CPU6502_SEFixture, SED_IMPL_CanSetCarryFlag){
    SE_CanSetFlag(SED_IMPL, CPU6502_Status_D);
}

TEST_F(CPU6502_SEFixture, SEI_IMPL_CanSetCarryFlag){
    SE_CanSetFlag(SEI_IMPL, CPU6502_Status_I);
}