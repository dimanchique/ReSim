#include "I8080_TestingSuite.h"

class I8080_ANIFixture : public I8080_TestFixture {
public:
    void ANI_CanDoImmediateAnd(BYTE accValue, BYTE memoryValue) {
        // given:
        cpu.A = accValue;
        mem[0x0000] = I8080_OpCodes::ANI;
        mem[0x0001] = memoryValue;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue & memoryValue);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

TEST_F(I8080_ANIFixture, ANI) {
    ANI_CanDoImmediateAnd(0b01111111, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANIFixture, ANI_Zero) {
    ANI_CanDoImmediateAnd(0b00000000, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANIFixture, ANI_Signed_NoParity) {
    ANI_CanDoImmediateAnd(0b10000011, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANIFixture, ANI_Signed_Parity) {
    ANI_CanDoImmediateAnd(0b10000001, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
