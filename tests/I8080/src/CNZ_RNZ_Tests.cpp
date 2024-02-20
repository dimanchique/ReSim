#include "I8080_TestingSuite.h"

class I8080_CNZ_RNZFixture : public I8080_TestFixture {
public:
    void CNZ_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.A = 0xFF;
        cpu.Status.Z = !canCall;
        mem[0x0000] = I8080_OpCodes::CNZ;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate Z flag change in runtime
        mem[0x3C00] = I8080_OpCodes::ANI;
        mem[0x3C01] = canReturn ? 0xFF : 0x00;
        mem[0x3C02] = I8080_OpCodes::RNZ;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CZ
        cyclesExpected += canCall ? 7 : 0;                          // ANI
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RZ

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, canCall ? (canReturn ? 0x0003 : 0x3C03) : 0x0003);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CNZ_RNZFixture, CNZ_CanCallAndCanReturn) {
    CNZ_CanCall(true, true);
}

TEST_F(I8080_CNZ_RNZFixture, CNZ_CanCallAndCannotReturn) {
    CNZ_CanCall(true, false);
}

TEST_F(I8080_CNZ_RNZFixture, CNZ_CannotCall) {
    CNZ_CanCall(false, false);
}