#include "I8080_TestingSuite.h"

using namespace ReSimFunctionLibrary::DataManipulation;

// We can directly set SP here but there are some problems with proper RET execution in this case
// We assume SP must be 0xFFFF at the end of test but if we set SP=(some value) there is no way to restore it back
// and check SPHL behavior so we need some indirect logic
class I8080_SPHLFixture : public I8080_TestFixture {
public:
    void SPHL_CanLoadSP(const WORD registerValue) {
        // given:
        cpu.DE = 0xFFFF;
        putLIWordToTwoBytes(registerValue, cpu.H, cpu.L);
        mem[registerValue] = 0xCD;
        mem[registerValue+1] = 0xAB;
        mem[0x0000] = SPHL;     // Set SP = HL
        mem[0x0001] = XTHL;     // Save HL to Stack Top
        mem[0x0002] = XCHG;     // DE <--> HL
        mem[0x0003] = SPHL;     // Set SP = HL (0xFFFF) <-- Stack top
        mem[0x0004] = RET;      // Return

        cyclesExpected = 5 + 18 + 5 + 5;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(putTwoBytesToLIWord(cpu.D, cpu.E), 0xABCD);
        CheckCyclesCount();
    }
};

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_1) {
    SPHL_CanLoadSP(0x2233);
}

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_2) {
    SPHL_CanLoadSP(0xAE29);
}

TEST_F(I8080_SPHLFixture, SPHL_CanLoadSP_3) {
    SPHL_CanLoadSP(0x506C);
}
