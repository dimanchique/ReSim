#include "I8080_TestingSuite.h"

class I8080_DADFixture : public I8080_TestFixture {
public:
    void DAD_CanDoDoubleAdd(const BYTE opCode,
                            const BYTE expectedH,
                            const BYTE expectedL,
                            const bool expectedCarry) {
        mem[0x0000] = opCode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.H, expectedH);
        EXPECT_EQ(cpu.L, expectedL);
        EXPECT_EQ(cpu.Status.C, expectedCarry);
        CheckCyclesCount();
    }
};

TEST_F(I8080_DADFixture, DAD_B1) {
    cpu.B = 0x33;
    cpu.C = 0x9F;
    cpu.H = 0xA1;
    cpu.L = 0x7B;
    DAD_CanDoDoubleAdd(DAD_B, 0xD5, 0x1A, false);
}

TEST_F(I8080_DADFixture, DAD_B2) {
    cpu.B = 0xF2;
    cpu.C = 0x3D;
    cpu.H = 0x1A;
    cpu.L = 0x34;
    DAD_CanDoDoubleAdd(DAD_B, 0x0C, 0x71, true);
}

TEST_F(I8080_DADFixture, DAD_D1) {
    cpu.D = 0x33;
    cpu.E = 0x9F;
    cpu.H = 0xA1;
    cpu.L = 0x7B;
    DAD_CanDoDoubleAdd(DAD_D, 0xD5, 0x1A, false);
}

TEST_F(I8080_DADFixture, DAD_D2) {
    cpu.D = 0xF2;
    cpu.E = 0x3D;
    cpu.H = 0x1A;
    cpu.L = 0x34;
    DAD_CanDoDoubleAdd(DAD_D, 0x0C, 0x71, true);
}

TEST_F(I8080_DADFixture, DAD_H1) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    DAD_CanDoDoubleAdd(DAD_H, 0x24, 0x68, false);
}

TEST_F(I8080_DADFixture, DAD_H2) {
    cpu.H = 0xF2;
    cpu.L = 0x3D;
    DAD_CanDoDoubleAdd(DAD_H, 0xE4, 0x7A, true);
}

TEST_F(I8080_DADFixture, DAD_SP1) {
    cpu.SP = 0x339F;
    cpu.H = 0xA1;
    cpu.L = 0x7B;
    DAD_CanDoDoubleAdd(DAD_SP, 0xD5, 0x1A, false);
}

TEST_F(I8080_DADFixture, DAD_SP2) {
    cpu.SP = 0xF23D;
    cpu.H = 0x1A;
    cpu.L = 0x34;
    DAD_CanDoDoubleAdd(DAD_SP, 0x0C, 0x71, true);
}
