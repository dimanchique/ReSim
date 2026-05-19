#include "I8086_ImpliedOpTests.h"

class I8086_CBW_CWD_Fixture : public I8086_ImpliedOpFixture {};

TEST_F(I8086_CBW_CWD_Fixture, CBW_CanConvert_1) {
    cpu.AH = 0x00;
    cpu.AL = 0xFF;
    TestImpliedInstruction(CBW);
    EXPECT_EQ(cpu.AH, 0xFF);
}

TEST_F(I8086_CBW_CWD_Fixture, CBW_CanConvert_2) {
    cpu.AH = 0xFF;
    cpu.AL = 0x0F;
    TestImpliedInstruction(CBW);
    EXPECT_EQ(cpu.AH, 0x00);
}

TEST_F(I8086_CBW_CWD_Fixture, CBW_CanConvert_3) {
    cpu.AH = 0x00;
    cpu.AL = 0x80;
    TestImpliedInstruction(CBW);
    EXPECT_EQ(cpu.AH, 0xFF);
}

TEST_F(I8086_CBW_CWD_Fixture, CBW_CanConvert_4) {
    cpu.AH = 0xFF;
    cpu.AL = 0x7F;
    TestImpliedInstruction(CBW);
    EXPECT_EQ(cpu.AH, 0x00);
}

TEST_F(I8086_CBW_CWD_Fixture, CWD_CanConvert_1) {
    cpu.DX = 0x0000;
    cpu.AX = 0xFFFF;
    TestImpliedInstruction(CWD);
    EXPECT_EQ(cpu.DX, 0xFFFF);
}

TEST_F(I8086_CBW_CWD_Fixture, CWD_CanConvert_2) {
    cpu.DX = 0xFFFF;
    cpu.AX = 0x00FF;
    TestImpliedInstruction(CWD);
    EXPECT_EQ(cpu.DX, 0x0000);
}

TEST_F(I8086_CBW_CWD_Fixture, CWD_CanConvert_3) {
    cpu.DX = 0x0000;
    cpu.AX = 0x8000;
    TestImpliedInstruction(CWD);
    EXPECT_EQ(cpu.DX, 0xFFFF);
}

TEST_F(I8086_CBW_CWD_Fixture, CWD_CanConvert_4) {
    cpu.DX = 0xFFFF;
    cpu.AX = 0x7FFF;
    TestImpliedInstruction(CWD);
    EXPECT_EQ(cpu.DX, 0x0000);
}
