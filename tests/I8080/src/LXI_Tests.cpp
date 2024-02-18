#include "I8080_TestingSuite.h"

class I8080_LXIFixture : public I8080_TestFixture {
public:
    void LXI_CanLoadImmediateValue(const I8080_OpCodes opcode, const WORD* targetRegisterPtr) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = 0x01;
        mem[0x0002] = 0x03;

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(*targetRegisterPtr, 0x0103);
        CheckCyclesCount();
    }
};

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueB) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.B);
    LXI_CanLoadImmediateValue(I8080_OpCodes::LXI_B, registerPtr);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueD) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.D);
    LXI_CanLoadImmediateValue(I8080_OpCodes::LXI_D, registerPtr);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueH) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.H);
    LXI_CanLoadImmediateValue(I8080_OpCodes::LXI_H, registerPtr);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueSP) {
    LXI_CanLoadImmediateValue(I8080_OpCodes::LXI_SP, &cpu.SP);
}

