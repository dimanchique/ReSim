#include "CPU6502_Tests.h"

class CPU6502_LDYFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_LDYFixture, LDY_IM_CanLoadValue){
    // given:
    BYTE OldY = 0x44;
    BYTE NewY = 0x04;
    cpu.Y = OldY;
    mem[0xFFFC] = CPU6502_OpCodes::LDY_IM;      // read value from the next mem cell
    mem[0xFFFD] = NewY;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.Y, OldY);
    EXPECT_EQ(cpu.Y, NewY);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_IM_CanAffectZeroFlag){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDY_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x0;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_IM_CanAffectNegativeFlag){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDY_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x80;                         // store this value in A register

    CPU6502 cpuCopy = cpu;

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ZP_CanLoadValue){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ZP;      // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0042] = 0x37;                         // store this value in A register

    const U32 NumCycles = 3;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ZPX_CanLoadValue){
    // given:
    cpu.X = 0x5;                                // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0047] = 0x37;                         // store this value in A register

    const U32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ZPX_CanLoadValue_WithWrap){
    // given:
    cpu.X = 0xFF;                               // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x80;                         // read value from memory using pointer
    mem[0x007F] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ABS_CanLoadValue){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480
    mem[0x4480] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ABSY_CanLoadValue){
    // given:
    cpu.X = 0x01;                               // preload 0x01 to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ABSX;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x80;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4480 + 0x0001 = 0x4481
    mem[0x4481] = 0x37;                         // store this value in A register

    const S32 NumCycles = 4;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}

TEST_F(CPU6502_LDYFixture, LDY_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing){
    // given:
    cpu.X = 0xFF;                               // preload 0xFF to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDY_ABSX;    // read the 16 bit Little Endian pointer from the next mem cell
    mem[0xFFFD] = 0x02;                         // read from this address
    mem[0xFFFE] = 0x44;                         // 0x4402 + 0x00FF = 0x4501 -> page crossing, so we need extra cycle
    mem[0x4501] = 0x37;                         // store this value in A register

    const S32 NumCycles = 5;
    CPU6502 cpuCopy = cpu;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.Y, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(CNT, NumCycles);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
}
