#include "CPU6502_Tests.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture{
};

TEST_F(CPU6502_CPUFixture, CpuDoesNothingWithZeroCycles) {
    // given:
    const U32 NumCycles = 0;

    // when:
    S32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(NumCycles, CNT);
}

TEST_F(CPU6502_CPUFixture, CpuCanExecuteMoreCyclesThenRequested) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x42;                         // store this value in A register

    // when:
    U32 CNT = cpu.Run(1, mem);                  // At least one instruction must be executed

    // then:
    EXPECT_EQ(CNT, 2);
}

TEST_F(CPU6502_CPUFixture, MemCheck) {
    // given:
    unsigned long long MemCellsSum = 0;

    // when:
    for(U32 i = 0; i < mem.GetSize(); ++i)
        MemCellsSum+=mem[i];

    // then:
    EXPECT_EQ(MemCellsSum, 0);
}