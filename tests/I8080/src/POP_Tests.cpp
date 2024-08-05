#include "I8080_TestingSuite.h"

class I8080_POPFixture : public I8080_TestFixture {
public:
    void POP_CanPOP(const I8080_OpCodes opcode, BYTE *lsb, BYTE *msb) {
        // given:
        cpu.SP = 0x1239;
        *lsb = 0;
        *msb = 0;
        const BYTE stackLSB = 0x93;
        const BYTE stackMSB = 0b11000111;
        mem[0x1239] = stackMSB;
        mem[0x123A] = stackLSB;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(stackLSB, *lsb);
        EXPECT_EQ(stackMSB, *msb);
        CheckCyclesCount();
    }
};

TEST_F(I8080_POPFixture, POP_CanPOPB) {
    POP_CanPOP(POP_B, &cpu.B, &cpu.C);
}

TEST_F(I8080_POPFixture, POP_CanPOPD) {
    POP_CanPOP(POP_D, &cpu.D, &cpu.E);
}

TEST_F(I8080_POPFixture, POP_CanPOPH) {
    POP_CanPOP(POP_H, &cpu.H, &cpu.L);
}

TEST_F(I8080_POPFixture, POP_CanPOPPSW) {
    POP_CanPOP(POP_PSW, &cpu.A, (BYTE*)&cpu.Status);
}

