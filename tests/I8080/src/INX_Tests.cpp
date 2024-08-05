#include "I8080_TestingSuite.h"

class I8080_INXFixture : public I8080_TestFixture {
public:
    void INX_CanIncrementValue(const I8080_OpCodes opcode, const WORD* targetRegisterPtr) {
        // given:
        WORD value = *targetRegisterPtr;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(*targetRegisterPtr, WORD(++value));
        CheckCyclesCount();
    }
};

TEST_F(I8080_INXFixture, INX_B_CanIncrement) {
    INX_CanIncrementValue(INX_B, reinterpret_cast<WORD*>(&cpu.B));
}

TEST_F(I8080_INXFixture, INX_B_CanIncrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.B);
    *registerPtr = 0x39FF;
    INX_CanIncrementValue(INX_B, registerPtr);
}

TEST_F(I8080_INXFixture, INX_D_CanIncrement) {
    INX_CanIncrementValue(INX_D, reinterpret_cast<WORD*>(&cpu.D));
}

TEST_F(I8080_INXFixture, INX_D_CanIncrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.D);
    *registerPtr = 0x39FF;
    INX_CanIncrementValue(INX_D, registerPtr);
}

TEST_F(I8080_INXFixture, INX_H_CanIncrement) {
    INX_CanIncrementValue(INX_H, reinterpret_cast<WORD*>(&cpu.H));
}

TEST_F(I8080_INXFixture, INX_H_CanIncrement_Overflowed) {
    WORD* registerPtr = reinterpret_cast<WORD*>(&cpu.H);
    *registerPtr = 0x39FF;
    INX_CanIncrementValue(INX_H, registerPtr);
}

TEST_F(I8080_INXFixture, INX_SP_CanIncrement) {
    INX_CanIncrementValue(INX_SP, &cpu.SP);
}

TEST_F(I8080_INXFixture, INX_SP_CanIncrement_Overflowed) {
    WORD* registerPtr = &cpu.SP;
    *registerPtr = 0x39FF;
    INX_CanIncrementValue(INX_SP, registerPtr);
}
