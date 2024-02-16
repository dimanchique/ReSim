#include "I8080_TestingSuite.h"

class I8080_SPHLFixture : public I8080_TestFixture {
public:
    void SPHL_CanLoadSP(const WORD registerValue) {
        // given:
        I8080::wordToRegisterSwapped(registerValue, cpu.H, cpu.L);
        mem[0x0000] = I8080_OpCodes::SPHL;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.SP, registerValue);
        CheckCyclesCount();
    }
};

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_1) {
    SPHL_CanLoadSP(0x2233);
}

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_2) {
    SPHL_CanLoadSP(0xAE29);
}

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_3) {
    SPHL_CanLoadSP(0x506C);
}

