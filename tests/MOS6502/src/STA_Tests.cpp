#include "MOS6502_ST_Tests.h"

class MOS6502_STAFixture : public MOS6502_STFixture{};

TEST_F(MOS6502_STAFixture, STA_ZP_CanStoreValue) {
    ST_ZP_CanStoreValue(STA_ZP, cpu.A);
}

TEST_F(MOS6502_STAFixture, STA_ZPX_CanStoreValue) {
    cpu.X = 0x0F;
    ST_ZP_CanStoreValue(STA_ZPX, cpu.A, cpu.X);
}

TEST_F(MOS6502_STAFixture, STA_ABS_CanStoreValue) {
    ST_ABS_CanStoreValue(STA_ABS, cpu.A);
}

TEST_F(MOS6502_STAFixture, STA_ABSX_CanStoreValue) {
    cpu.X = 0x0F;
    ST_ABS_CanStoreValue(STA_ABSX, cpu.A, cpu.X);
}

TEST_F(MOS6502_STAFixture, STA_ABSY_CanStoreValue) {
    cpu.Y = 0x0F;
    ST_ABS_CanStoreValue(STA_ABSY, cpu.A, cpu.Y);
}

TEST_F(MOS6502_STAFixture, STA_INDX_CanStoreValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFFFC] = MOS6502_OpCodes::STA_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address from 0x0006-0x0007
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x00;                         // store A value in this mem cell

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x8000], cpu.A);
    CheckCyclesCount();
}

TEST_F(MOS6502_STAFixture, STA_INDY_CanStoreValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFFFC] = MOS6502_OpCodes::STA_INDY;    // read the 8 bit value from the next mem cell
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (add Y) = 0x8004
    mem[0x8004] = 0x00;                         // store A value in this mem cell

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x8004], cpu.A);
    CheckCyclesCount();
}