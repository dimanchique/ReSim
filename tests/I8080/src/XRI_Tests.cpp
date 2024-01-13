#include "I8080_TestingSuite.h"

class I8080_XRIFixture : public I8080_TestFixture {
public:
    void XRI_CanDoImmediateAnd(BYTE accValue, BYTE memoryValue) {
        // given:
        cpu.A = accValue;
        mem[0x0000] = I8080_OpCodes::XRI;
        mem[0x0001] = memoryValue;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue ^ memoryValue);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

TEST_F(I8080_XRIFixture, XRI) {
    XRI_CanDoImmediateAnd(0b00101010, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRIFixture, XRI_Zero) {
    XRI_CanDoImmediateAnd(0b00000000, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRIFixture, XRI_Signed_NoParity) {
    XRI_CanDoImmediateAnd(0b10000011, 0b00000000); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRIFixture, XRI_Signed_Parity) {
    XRI_CanDoImmediateAnd(0b10000001, 0b01000010); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
