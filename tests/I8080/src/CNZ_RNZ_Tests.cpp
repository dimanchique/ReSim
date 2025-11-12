#include "I8080_TestingSuite.h"

class I8080_CNZ_RNZFixture : public I8080_TestFixture {
public:
    void CNZ_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.A = 0xFF;
        cpu.Status.Z = !canCall;
        mem[0x0000] = CNZ;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate Z flag change in runtime
        mem[0x003C] = ANI;
        mem[0x003D] = canReturn ? 0xFF : 0x00;
        mem[0x003E] = RNZ;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CZ
        cyclesExpected += canCall ? 7 : 0;                          // ANI
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RZ

        const WORD targetPC = canCall ? (canReturn ? 0x0003 : 0x003E) : 0x0003;
        mem[targetPC] = RET;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(cpu.PC, targetPC);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CNZ_RNZFixture, CNZ_CanCallAndCanReturn) {
    CNZ_CanCall(true, true);
}

TEST_F(I8080_CNZ_RNZFixture, CNZ_CannotCall) {
    CNZ_CanCall(false, false);
}
