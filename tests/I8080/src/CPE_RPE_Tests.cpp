#include "I8080_TestingSuite.h"

class I8080_CPE_RPEFixture : public I8080_TestFixture {
public:
    void CPE_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.A = canCall ? 0b11111111 : 0b11111110;
        cpu.Status.P = canCall;
        mem[0x0000] = CPE;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate Parity flag change in runtime
        mem[0x3C00] = ANI;
        mem[0x3C01] = canReturn ? 0b11111111 : 0b11111110;
        mem[0x3C02] = RPE;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CPE
        cyclesExpected += canCall ? 7 : 0;                          // ANI
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RPE

        const WORD targetPC = canCall ? (canReturn ? 0x0003 : 0x3C03) : 0x0003;
        mem[targetPC] = STOP_OPCODE;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, targetPC);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CPE_RPEFixture, CPE_CanCallAndCanReturn) {
    CPE_CanCall(true, true);
}

TEST_F(I8080_CPE_RPEFixture, CPE_CanCallAndCannotReturn) {
    CPE_CanCall(true, false);
}

TEST_F(I8080_CPE_RPEFixture, CPE_CannotCall) {
    CPE_CanCall(false, false);
}