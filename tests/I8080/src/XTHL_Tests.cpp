#include "I8080_TestingSuite.h"

class I8080_XTHLFixture : public I8080_TestFixture {
public:
    // We can directly set SP here but there are some problems with proper RET execution in this case
    // We assume SP must be 0xFFFF at the end of test but if we set SP=(some value) there is no way to restore it back
    // and check XTHL behavior so we need some indirect logic
    void XTHL_CanExchangeValues(const WORD stackPointerValue, const WORD registerValueH) {
        // given:
        cpu.BC = stackPointerValue;     // save stackPointerValue to BC
        ReSimFunctionLibrary::DataManipulation::putLIWordToTwoBytes(registerValueH, cpu.H, cpu.L);
        mem[0x0000] = PUSH_B;           // Push BC value (stackPointerValue) to stack
        mem[0x0001] = XTHL;             // HL <--> mem[SP]
        mem[0x0002] = POP_B;            // Pop Stack top to BC to restore stack size for proper return
        mem[0x0003] = RET;

        cyclesExpected = 11 + 18 + 10;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        const WORD swappedValueH = cpu.HL;
        const WORD swappedValueStackPointer = *reinterpret_cast<WORD*>(&mem[cpu.SP - 2]);
        EXPECT_EQ(swappedValueStackPointer, registerValueH);
        EXPECT_EQ(swappedValueH, stackPointerValue);
        CheckCyclesCount();
    }
};

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_1) {
    XTHL_CanExchangeValues(0x1234, 0x2345);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_2) {
    XTHL_CanExchangeValues(0xABBA, 0xFF00);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_3) {
    XTHL_CanExchangeValues(0xAADD, 0xDEAD);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_4) {
    XTHL_CanExchangeValues(0xF00D, 0x0B3C);
}
