#include "I8086_TestingSuite.h"
#include "I8086_OpCodes_Groups.h"

TEST_F(I8086_TestFixture, CALL_Ap) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    mem[0x11000] = CALL_Ap;
    mem[0x11001] = 0x00;
    mem[0x11002] = 0x01; // New PC = 0x0100
    mem[0x11003] = 0x00;
    mem[0x11004] = 0x20; // New CS = 0x2000
    mem[0x20100] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0100);
    EXPECT_EQ(cpu.SP, 0x6000 - 4);
}

TEST_F(I8086_TestFixture, CALL_Jv) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    mem[0x11000] = CALL_Jv;
    mem[0x11001] = 0x00;
    mem[0x11002] = 0x01; // PC offset = +0x0100
    mem[0x11103] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x1103);
    EXPECT_EQ(cpu.SP, 0x6000 - 2);
}

TEST_F(I8086_TestFixture, CALL_GRP5_FarIndirect_Address) {
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    ModRegByte modReg;
    modReg.mod = 0b00; // Addr
    modReg.reg = I8086_OpCodes_GRP5::GRP5_CALL;
    modReg.rm = 0b111; // [BX]

    mem[0x11000] = GRP5_Ev;
    mem[0x11001] = modReg.value;

    cpu.DS = 0x2000;
    cpu.BX = 0x3000;
    mem[0x23000] = 0x78;
    mem[0x23001] = 0x56; // Offset

    mem[0x15678] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    EXPECT_EQ(cpu.PC, 0x5678);
    EXPECT_EQ(cpu.SP, 0x5FFE); // SP decreased by 2
}

TEST_F(I8086_TestFixture, CALL_GRP5_MP_FarIndirect_Address) {
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    ModRegByte modReg;
    modReg.mod = 0b00; // Addr
    modReg.reg = I8086_OpCodes_GRP5::GRP5_CALL_Mp;
    modReg.rm = 0b111; // [BX]

    mem[0x11000] = GRP5_Ev;
    mem[0x11001] = modReg.value;

    cpu.DS = 0x2000;
    cpu.BX = 0x3000;
    mem[0x23000] = 0x78;
    mem[0x23001] = 0x56; // Offset
    mem[0x23002] = 0x34;
    mem[0x23003] = 0x12; // Segment

    mem[0x179B8] = I8086_STOP_OPCODE;

    cyclesPassed = cpu.Run();

    EXPECT_EQ(cpu.CS, 0x1234);
    EXPECT_EQ(cpu.PC, 0x5678);
    EXPECT_EQ(cpu.SP, 0x5FFC); // SP decreased by 4
}
