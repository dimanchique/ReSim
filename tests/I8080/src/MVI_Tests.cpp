#include "I8080_TestingSuite.h"

class I8080_MVIFixture : public I8080_TestFixture {
public:
    void MVI_CanMoveToReg(const I8080_OpCodes opcode, const BYTE &targetRegister, const BYTE immediateValue) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = immediateValue;
        mem[0x0002] = STOP_OPCODE;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(targetRegister, immediateValue);
        CheckCyclesCount();
    }

    void MVI_CanMoveToMem(const BYTE immediateValue, const WORD memoryAddress) {
        // given:
        mem[0x0000] = MVI_M;
        mem[0x0001] = immediateValue;
        mem[0x0002] = STOP_OPCODE;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(memoryAddress, cpu.H, cpu.L);

        cyclesExpected = 10;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], immediateValue);
        CheckCyclesCount();
    }
};

TEST_F(I8080_MVIFixture, MVI_A) {
    MVI_CanMoveToReg(MVI_A, cpu.A, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_B) {
    MVI_CanMoveToReg(MVI_B, cpu.B, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_C) {
    MVI_CanMoveToReg(MVI_C, cpu.C, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_D) {
    MVI_CanMoveToReg(MVI_D, cpu.D, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_E) {
    MVI_CanMoveToReg(MVI_E, cpu.E, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_H) {
    MVI_CanMoveToReg(MVI_H, cpu.H, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_L) {
    MVI_CanMoveToReg(MVI_L, cpu.L, 0x25);
}

TEST_F(I8080_MVIFixture, MVI_M) {
    MVI_CanMoveToMem(0x25, 0x1234);
}
