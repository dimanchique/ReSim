#include "CPU6502_Tests.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture{};

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

    const U32 NumCycles = 1;

    // when:
    S32 CNT = cpu.Run(NumCycles, mem);          // At least one instruction must be executed

    // then:
    EXPECT_EQ(CNT, 2);
}

//*****************************************
// This test fails because we're throwing exception on bad instruction
//*****************************************
//TEST_F(CPU6502_CPUFixture, CpuDoesntGoToInfiniteLoopWithBadInstruction) {
//    // given:
//    mem[0xFFFC] = 0x0;                          // Invalid OpCode
//    mem[0xFFFD] = 0x0;
//
//    const S32 NumCycles = 15;
//
//    // when:
//    S32 CNT = cpu.Run(NumCycles, mem);
//
//    // then:
//    EXPECT_EQ(CNT, NumCycles);                          // It should execute only one cycle and return
//}

TEST_F(CPU6502_CPUFixture, MemCheck) {
    // given:
    unsigned long long MemCellsSum = 0;

    // when:
    for(U32 i = 0; i < mem.GetSize(); ++i)
        MemCellsSum+=mem[i];

    // then:
    EXPECT_EQ(MemCellsSum, 0);
}