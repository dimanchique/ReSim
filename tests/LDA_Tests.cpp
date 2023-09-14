#include "CPU6502_LD_Tests.h"

class CPU6502_LDAFixture : public CPU6502_LDFixture{};

TEST_F(CPU6502_LDAFixture, LDA_IM_CanLoadValue){
    LD_IM_CanLoadValue(CPU6502_OpCodes::LDA_IM, cpu.A);
}

TEST_F(CPU6502_LDAFixture, LDA_IM_CanAffectZeroFlag){
    LD_IM_CanAffectZeroFlag(CPU6502_OpCodes::LDA_IM);
}

TEST_F(CPU6502_LDAFixture, LDA_IM_CanAffectNegativeFlag){
    LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes::LDA_IM);
}

TEST_F(CPU6502_LDAFixture, LDA_ZP_CanLoadValue){
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDA_ZP, cpu.A);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX_CanLoadValue){
    cpu.X = 0x5;
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDA_ZPX, cpu.A, cpu.X);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX_CanLoadValue_WithWrap){
    cpu.X = 0xFF;
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDA_ZPX, cpu.A, cpu.X);
}

TEST_F(CPU6502_LDAFixture, LDA_ABS_CanLoadValue){
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDA_ABS, cpu.A);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSX_CanLoadValue){
    cpu.X = 0x01;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDA_ABSX, cpu.A, cpu.X);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSX_CanLoadValue_WithExtraCycleOnPageCrossing){
    cpu.X = 0xFF;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDA_ABSX, cpu.A, cpu.X);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSY_CanLoadValue){
    cpu.Y = 0x01;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDA_ABSY, cpu.A, cpu.Y);
}

TEST_F(CPU6502_LDAFixture, LDA_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing){
    cpu.Y = 0xFF;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDA_ABSY, cpu.A, cpu.Y);
}

TEST_F(CPU6502_LDAFixture, LDA_INDX_CanLoadValue){
    // given:
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address from 0x0006-0x0007
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x37;                         // store this value in A register

    const S32 NumCycles = 6;

    // when:
    CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_LDAFixture, LDA_INDY_CanLoadValue){
    // given:
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDY;    // read the 8 bit value from the next mem cell
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (add Y) = 0x8004
    mem[0x8004] = 0x37;                         // store this value in A register

    const S32 NumCycles = 5;

    // when:
    CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_LDAFixture, LDA_INDY_CanLoadValueWithExtraCycleOnPageCrossing){
    // given:
    cpu.Y = 0xFF;                               // preload FF to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::LDA_INDY;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x02;                         //
    mem[0x0003] = 0x80;                         // 0x8002 + 0x00FF (Y) = 0x8101 -> page crossing, so we need extra cycle
    mem[0x8101] = 0x37;                         // store this value in A register

    const S32 NumCycles = 6;

    // when:
    CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_EQ(CNT, NumCycles);
}
