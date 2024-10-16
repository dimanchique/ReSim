#include "I8080_TestingSuite.h"

class I8080_LXIFixture : public I8080_TestFixture {
public:
    void LXI_CanLoadImmediateValue(const I8080_OpCodes opcode, const WORD& targetRegisterPtr) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = 0x01;
        mem[0x0002] = 0x03;
        mem[0x0003] = STOP_OPCODE;

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(targetRegisterPtr, 0x0103);
        CheckCyclesCount();
    }
};

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueB) {
    LXI_CanLoadImmediateValue(LXI_B, cpu.BC);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueD) {
    LXI_CanLoadImmediateValue(LXI_D, cpu.DE);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueH) {
    LXI_CanLoadImmediateValue(LXI_H, cpu.HL);
}

TEST_F(I8080_LXIFixture, LXI_CanLoadImidiateValueSP) {
    LXI_CanLoadImmediateValue(LXI_SP, cpu.SP);
}

