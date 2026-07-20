#include "I8080_TestingSuite.h"

class I8080_INXFixture : public I8080_TestFixture {
public:
    void INX_CanIncrementValue(const I8080_OpCodes_Main opcode, const WORD* targetRegisterPtr) {
        // given:
        WORD value = *targetRegisterPtr;
        mem[0x0000] = opcode;
        mem[0x0001] = RET;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(*targetRegisterPtr, WORD(++value));
        CheckCyclesCount();
    }
};

TEST_F(I8080_INXFixture, INX_B_CanIncrement) {
    INX_CanIncrementValue(INX_B, &cpu.BC);
}

TEST_F(I8080_INXFixture, INX_B_CanIncrement_Overflowed) {
    cpu.BC = 0x39FF;
    INX_CanIncrementValue(INX_B, &cpu.BC);
}

TEST_F(I8080_INXFixture, INX_D_CanIncrement) {
    INX_CanIncrementValue(INX_D, &cpu.DE);
}

TEST_F(I8080_INXFixture, INX_D_CanIncrement_Overflowed) {
    cpu.DE = 0x39FF;
    INX_CanIncrementValue(INX_D, &cpu.DE);
}

TEST_F(I8080_INXFixture, INX_H_CanIncrement) {
    INX_CanIncrementValue(INX_H, &cpu.HL);
}

TEST_F(I8080_INXFixture, INX_H_CanIncrement_Overflowed) {
    cpu.HL = 0x39FF;
    INX_CanIncrementValue(INX_H, &cpu.HL);
}

//TEST_F(I8080_INXFixture, INX_SP_CanIncrement) {
//    INX_CanIncrementValue(INX_SP, &cpu.SP);
//}
//
//TEST_F(I8080_INXFixture, INX_SP_CanIncrement_Overflowed) {
//    cpu.SP = 0x39FF;
//    INX_CanIncrementValue(INX_SP, &cpu.SP);
//}
