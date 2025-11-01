#include "I8086_TestingSuite.h"

class I8086_LOAD_Fixture : public I8086_TestFixture{};

TEST_F(I8086_LOAD_Fixture, LOAD_Gv_M) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.DS = 0x2800;
    cpu.BX = 0x0400;
    cpu.SI = 0x003C;

    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Reg;
    modReg.leftOp.regData = wBX;

    modReg.rightOp.archetype = OperandArchetype::Mem;
    modReg.rightOp.memData.mode = modeBXpSI;
    modReg.rightOp.memData.dispSize = 2;
    modReg.rightOp.memData.dispValue = 0x0F62;

    mem[effectiveAddress++] = LEA_Gv_M;
    mem[effectiveAddress++] = modReg.MakeModByte();
    mem[effectiveAddress++] = 0x62;
    mem[effectiveAddress++] = 0x0F;
    mem[effectiveAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.BX, 0x139E);
}

TEST_F(I8086_LOAD_Fixture, LES_Gv_Mp) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.DS = 0x2800;
    cpu.BX = 0x0400;
    cpu.SI = 0x003C;

    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Reg;
    modReg.leftOp.regData = wBX;

    modReg.rightOp.archetype = OperandArchetype::Mem;
    modReg.rightOp.memData.mode = modeBXpSI;
    modReg.rightOp.memData.dispSize = 2;
    modReg.rightOp.memData.dispValue = 0x0F62;

    mem[effectiveAddress++] = LES_Gv_Mp;
    mem[effectiveAddress++] = modReg.MakeModByte();
    mem[effectiveAddress++] = 0x62;
    mem[effectiveAddress++] = 0x0F;
    mem[effectiveAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    // EA here is 0x2939E
    EXPECT_EQ(cpu.BX, 0x0002);
    EXPECT_EQ(cpu.ES, 0x939E);
}

TEST_F(I8086_LOAD_Fixture, LDS_Gv_Mp) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    cpu.DS = 0x2800;
    cpu.BX = 0x0400;
    cpu.SI = 0x003C;

    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Reg;
    modReg.leftOp.regData = wBX;

    modReg.rightOp.archetype = OperandArchetype::Mem;
    modReg.rightOp.memData.mode = modeBXpSI;
    modReg.rightOp.memData.dispSize = 2;
    modReg.rightOp.memData.dispValue = 0x0F62;

    mem[effectiveAddress++] = LDS_Gv_Mp;
    mem[effectiveAddress++] = modReg.MakeModByte();
    mem[effectiveAddress++] = 0x62;
    mem[effectiveAddress++] = 0x0F;
    mem[effectiveAddress++] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    // EA here is 0x2939E
    EXPECT_EQ(cpu.BX, 0x0002);
    EXPECT_EQ(cpu.DS, 0x939E);
}
