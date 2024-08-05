#include "I8080_TestingSuite.h"

class I8080_DCXFixture : public I8080_TestFixture {
public:
    void DCX_CanDecrementValue(const I8080_OpCodes opcode, const WORD* targetRegisterPtr) {
        // given:
        WORD value = *targetRegisterPtr;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(*targetRegisterPtr, WORD(--value));
        CheckCyclesCount();
    }
};

TEST_F(I8080_DCXFixture, DCX_B_CanDecrement) {
    DCX_CanDecrementValue(DCX_B, reinterpret_cast<WORD*>(&cpu.B));
}

TEST_F(I8080_DCXFixture, DCX_B_CanDecrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.B);
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_B, registerPtr);
}

TEST_F(I8080_DCXFixture, DCX_D_CanDecrement) {
    DCX_CanDecrementValue(DCX_D, reinterpret_cast<WORD*>(&cpu.D));
}

TEST_F(I8080_DCXFixture, DCX_D_CanDecrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.D);
    *registerPtr = 0x3900;
    DCX_CanDecrementValue(DCX_D, registerPtr);
}

TEST_F(I8080_DCXFixture, DCX_H_CanDecrement) {
    DCX_CanDecrementValue(DCX_H, reinterpret_cast<WORD*>(&cpu.H));
}

TEST_F(I8080_DCXFixture, DCX_H_CanDecrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.H);
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
