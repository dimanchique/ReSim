#include "I8080_TestingSuite.h"

class I8080_SHLDFixture : public I8080_TestFixture {
public:
    void SHLD_CanStoreHL(const WORD registerValue, const WORD memoryAddress) {
        // given:
        I8080::wordToRegisterSwapped(registerValue, cpu.H, cpu.L);
        mem[0x0000] = I8080_OpCodes::SHLD;
        I8080::wordToRegisterSwapped(memoryAddress, mem[0x0001], mem[0x0002]);

        cyclesExpected = 16;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], cpu.L);
        EXPECT_EQ(mem[memoryAddress+1], cpu.H);
        CheckCyclesCount();
    }
};

TEST_F(I8080_SHLDFixture, SHLD_CanStoreHL_1) {
    SHLD_CanStoreHL(0x2233, 0x1234);
}

TEST_F(I8080_SHLDFixture, SHLD_CanStoreHL_2) {
    SHLD_CanStoreHL(0xAE29, 0x010A);
}

