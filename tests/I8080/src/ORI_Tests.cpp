#include "I8080_TestingSuite.h"

class I8080_ORIFixture : public I8080_TestFixture {
public:
    void ORI_CanDoImmediateOr(const BYTE accValue, const BYTE memoryValue) {
        // given:
        cpu.A = accValue;
        mem[0x0000] = I8080_OpCodes::ORI;
        mem[0x0001] = memoryValue;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue | memoryValue);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

TEST_F(I8080_ORIFixture, ORI) {
    ORI_CanDoImmediateOr(0x1F, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORIFixture, ORI_Zero) {
    ORI_CanDoImmediateOr(0x0, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORIFixture, ORI_Signed_NoParity) {
    ORI_CanDoImmediateOr(0x80, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORIFixture, ORI_Signed_Parity) {
    ORI_CanDoImmediateOr(0x80, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
