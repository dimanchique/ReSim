#include "I8080_TestingSuite.h"

class I8080_CP_RPFixture : public I8080_TestFixture {
public:
    void CP_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.A = 0xFF;
        cpu.Status.S = !canCall;
        mem[0x0000] = I8080_OpCodes::CP;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate Z flag change in runtime
        mem[0x3C00] = I8080_OpCodes::ANI;
        mem[0x3C01] = canReturn ? 0x00 : 0xFF;
        mem[0x3C02] = I8080_OpCodes::RP;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CP
        cyclesExpected += canCall ? 7 : 0;                          // ANI
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RP

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, canCall ? (canReturn ? 0x0003 : 0x3C03) : 0x0003);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CP_RPFixture, CP_CanCallAndCanReturn) {
    CP_CanCall(true, true);
}

TEST_F(I8080_CP_RPFixture, CP_CanCallAndCannotReturn) {
    CP_CanCall(true, false);
}

TEST_F(I8080_CP_RPFixture, CP_CannotCall) {
    CP_CanCall(false, false);
}