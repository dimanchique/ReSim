#include "I8080_TestingSuite.h"

class I8080_CC_RCFixture : public I8080_TestFixture {
public:
    void CC_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.Status.C = canCall;
        mem[0x0000] = I8080_OpCodes::CC;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate C flag change in runtime
        mem[0x3C00] = canCall == canReturn ? I8080_OpCodes::NOP : I8080_OpCodes::CMC;
        mem[0x3C01] = I8080_OpCodes::RC;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CC
        cyclesExpected += canCall ? 4 : 0;                          // NOP/CMC
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RC

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, canCall ? (canReturn ? 0x0003 : 0x3C02) : 0x0003);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CC_RCFixture, CC_CanCallAndCanReturn) {
    CC_CanCall(true, true);
}

TEST_F(I8080_CC_RCFixture, CC_CanCallAndCannotReturn) {
    CC_CanCall(true, false);
}

TEST_F(I8080_CC_RCFixture, CC_CannotCall) {
    CC_CanCall(false, false);
}