#include "I8080_TestingSuite.h"

class I8080_CM_RMFixture : public I8080_TestFixture {
public:
    void CM_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.A = 0xFF;
        cpu.Status.S = canCall;
        mem[0x0000] = I8080_OpCodes::CM;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate Z flag change in runtime
        mem[0x3C00] = I8080_OpCodes::ANI;
        mem[0x3C01] = canReturn ? 0xFF : 0x00;
        mem[0x3C02] = I8080_OpCodes::RM;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CM
        cyclesExpected += canCall ? 7 : 0;                          // ANI
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RM

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, canCall ? (canReturn ? 0x0003 : 0x3C03) : 0x0003);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CM_RMFixture, CM_CanCallAndCanReturn) {
    CM_CanCall(true, true);
}

TEST_F(I8080_CM_RMFixture, CM_CanCallAndCannotReturn) {
    CM_CanCall(true, false);
}

TEST_F(I8080_CM_RMFixture, CM_CannotCall) {
    CM_CanCall(false, false);
}