#include "I8080_TestingSuite.h"

class I8080_DAAFixture : public I8080_TestFixture {
public:
    void DAA_CanDecimalAdjustAccumulator(const BYTE initialAccumulator,
                                         const BYTE expectedAccumulator,
                                         const bool initialAC,
                                         const bool expectedAC,
                                         const bool initialCarry,
                                         const bool expectedCarry) {
        cpu.A = initialAccumulator;
        cpu.Status.AC = initialAC;
        cpu.Status.C = initialCarry;
        mem[0x0000] = I8080_OpCodes::DAA;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedAccumulator);
        EXPECT_EQ(cpu.Status.AC, expectedAC);
        EXPECT_EQ(cpu.Status.C, expectedCarry);
        CheckCyclesCount();
    }
};

TEST_F(I8080_DAAFixture, DAA_1) {
    DAA_CanDecimalAdjustAccumulator(0x9B, 0x01, false, true, false, true);
}

TEST_F(I8080_DAAFixture, DAA_2) {
    DAA_CanDecimalAdjustAccumulator(0x9A, 0x00, false, true, false, true);
}

TEST_F(I8080_DAAFixture, DAA_3) {
    DAA_CanDecimalAdjustAccumulator(0x03, 0x09, true, false, false, false);
}

TEST_F(I8080_DAAFixture, DAA_4) {
    DAA_CanDecimalAdjustAccumulator(0x25, 0x8B, true, false, true, false);
}

TEST_F(I8080_DAAFixture, DAA_5) {
    DAA_CanDecimalAdjustAccumulator(0x28, 0x2E, true, false, false, false);
}
