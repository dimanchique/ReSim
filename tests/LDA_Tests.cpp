#include "CPU6502_Tests.h"

class CPU6502_LDAFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_LDAFixture, LDA_IM_CanLoadValue){
    // given:
    BYTE OldA = 0x44;
    BYTE NewA = 0x04;
    cpu.A = OldA;
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = NewA;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.A, OldA);
    EXPECT_EQ(cpu.A, NewA);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_IM_CanAffectZeroFlag){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x0;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_IM_CanAffectNegativeFlag){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x80;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ZP_CanLoadValue){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZP;      // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0042] = 0x37;                         // store this value in A register

    const U32 NumCycles = 3;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX_CanLoadValue){
    // given:
    cpu.X = 0x5;                                // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0047] = 0x37;                         // store this value in A register

    const U32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX_CanLoadValue_WithWrap){
    // given:
    cpu.X = 0xFF;                               // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x80;                         // read value from memory using pointer
    mem[0x007F] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ABS_CanLoadValue){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480
    mem[0x4480] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSX_CanLoadValue){
    // given:
    cpu.X = 0x01;                               // preload 0x01 to X to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ABSX;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480 + 0x0001 = 0x4481
    mem[0x4481] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSX_CanLoadValue_WithExtraCycleOnPageCrossing){
    // given:
    cpu.X = 0xFF;                               // preload 0xFF to X to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ABSX;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x02;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4402 + 0x00FF = 0x4501 -> page crossing, so we need extra cycle
    mem[0x4501] = 0x37;                         // store this value in A register

    const S32 NumCycles = 5;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSY_CanLoadValue){
    // given:
    cpu.Y = 0x01;                               // preload 0x01 to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ABSY;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480 + 0x0001 = 0x4481
    mem[0x4481] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing){
    // given:
    cpu.Y = 0xFF;                               // preload 0xFF to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ABSY;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x02;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4402 + 0x00FF = 0x4501 -> page crossing, so we need extra cycle
    mem[0x4501] = 0x37;                         // store this value in A register

    const S32 NumCycles = 5;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_INDX_CanLoadValue){
    // given:
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x37;                         // store this value in A register

    const S32 NumCycles = 6;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_INDY_CanLoadValue){
    // given:
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDY;    // read the 8 bit value from the next mem cell and add Y
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (Y) = 0x8004
    mem[0x8004] = 0x37;                         // store this value in A register

    const S32 NumCycles = 5;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDAFixture, LDA_INDY_CanLoadValue_WithExtraCycleOnPageCrossing){
    // given:
    cpu.Y = 0xFF;                               // preload FF to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDY;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x02;                         //
    mem[0x0003] = 0x80;                         // 0x8002 + 0x00FF (Y) = 0x8101 -> page crossing, so we need extra cycle
    mem[0x8101] = 0x37;                         // store this value in A register

    const S32 NumCycles = 6;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}
