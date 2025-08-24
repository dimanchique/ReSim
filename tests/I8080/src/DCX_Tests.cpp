#include "I8080_TestingSuite.h"

class I8080_DCXFixture : public I8080_TestFixture {
public:
    void DCX_CanDecrementValue(const I8080_OpCodes_Main opcode, const WORD* targetRegisterPtr) {
        // given:
        WORD value = *targetRegisterPtr;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        value -= 1;
        EXPECT_EQ(*targetRegisterPtr, WORD(value));
        CheckCyclesCount();
    }
};

TEST_F(I8080_DCXFixture, DCX_B_CanDecrement) {
    DCX_CanDecrementValue(DCX_B, &cpu.BC);
}

TEST_F(I8080_DCXFixture, DCX_B_CanDecrement_Overflowed) {
    WORD* registerPtr = &cpu.BC;
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_B, registerPtr);
}

TEST_F(I8080_DCXFixture, DCX_D_CanDecrement) {
    DCX_CanDecrementValue(DCX_D, &cpu.DE);
}

TEST_F(I8080_DCXFixture, DCX_D_CanDecrement_Overflowed) {
    WORD* registerPtr = &cpu.DE;
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_D, registerPtr);
}

TEST_F(I8080_DCXFixture, DCX_H_CanDecrement) {
    DCX_CanDecrementValue(DCX_H, &cpu.HL);
}

TEST_F(I8080_DCXFixture, DCX_H_CanDecrement_Overflowed) {
    WORD* registerPtr = &cpu.HL;
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_H, registerPtr);
}

TEST_F(I8080_DCXFixture, DCX_SP_CanDecrement) {
    DCX_CanDecrementValue(DCX_SP, &cpu.SP);
}

TEST_F(I8080_DCXFixture, DCX_SP_CanDecrement_Overflowed) {
    WORD* registerPtr = &cpu.SP;
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_SP, registerPtr);
}
