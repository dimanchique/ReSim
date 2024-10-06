#include "I8086_TestingSuite.h"

class I8086_ORFixture : public I8086_TestFixture {
public:

    void OR_CanDo_OR_Ev_Gv(DWORD memAddress, WORD memValue, WORD refReg, ModRegByteConstructor &modReg) {
        // given:
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        DWORD effectiveAddress = cpu.PC + (cpu.CS << 4);

        mem[memAddress] = memValue & 0xFF;
        mem[memAddress + 1] = (memValue >> 8) & 0xFF;

        modReg.size = OperandSize::WORD;
        BYTE modRegByte = modReg.MakeModByte();

        mem[effectiveAddress++] = OR_Ev_Gv;
        mem[effectiveAddress++] = modRegByte;

        if (modReg.leftOp.memData.mode == modeDirect) {
            mem[effectiveAddress++] = memAddress & 0xFF;
            mem[effectiveAddress++] = (memAddress >> 8) & 0xFF;
        }

        if (modReg.leftOp.memData.dispSize > 0) {
            mem[effectiveAddress++] = modReg.leftOp.memData.dispValue & 0xFF;
            if (modReg.leftOp.memData.dispSize > 1)
                mem[effectiveAddress++] = (modReg.leftOp.memData.dispValue >> 8) & 0xFF;
        }

        mem[effectiveAddress++] = STOP_OPCODE;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        // Result of ExGx is always in memory
        WORD result = mem[memAddress];
        result |= (mem[memAddress + 1] << 8);
        EXPECT_EQ(result, refReg | memValue);
    }

    template<typename T>
    void OR_CanDo_OR_AI(T initialValue, T memValue) {
        // given:
        cpu.PC = 0x1000;
        cpu.CS = 0x1000;
        DWORD effectiveAddress = cpu.PC + (cpu.CS << 4);

        if (std::is_same_v<T, BYTE>)
            cpu.AL = initialValue;
        else
            cpu.AX = initialValue;

        mem[effectiveAddress++] = std::is_same_v<T, BYTE> ? OR_AL_Ib : OR_AX_Iv;
        mem[effectiveAddress++] = memValue & 0xFF;
        if (!std::is_same_v<T, BYTE>)
            mem[effectiveAddress++] = (memValue >> 8) & 0xFF;
        mem[effectiveAddress] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        EXPECT_EQ((std::is_same_v<T, BYTE> ? cpu.AL : cpu.AX), initialValue | memValue);
    }
};

TEST_F(I8086_ORFixture, OR_Ev_Gv_FromBX_Addressed_to_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);

    OR_CanDo_OR_Ev_Gv(memAddress, memValue, cpu.AX, modReg);
}

TEST_F(I8086_ORFixture, OR_Ev_Gv_FromDirectAddressed_to_BX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wBX;

    cpu.BX = 0x0060;
    
    const WORD memValue = 0x12C;
    const DWORD memAddress = 0x1000;
    
    OR_CanDo_OR_Ev_Gv(memAddress, memValue, cpu.BX, modReg);
}

TEST_F(I8086_ORFixture, OR_Ev_Gv_FromBP_Addressed_to_DX_WithDisp) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wDX;

    cpu.DX = 0x0060;
    cpu.SS = 0x2000; // BP is force-replacing by SS
    
    const WORD memValue = 0x12C;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);
    
    OR_CanDo_OR_Ev_Gv(memAddress, memValue, cpu.DX, modReg);
}

TEST_F(I8086_ORFixture, OR_Ev_Gv_FromBXSI_Addressed_to_AX_WithDisp) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData.wordReg = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);
    
    OR_CanDo_OR_Ev_Gv(memAddress, memValue, cpu.AX, modReg);
}

TEST_F(I8086_ORFixture, OR_AL_Ib_Test1) {
    OR_CanDo_OR_AI<BYTE>(0x11, 0x22);
}

TEST_F(I8086_ORFixture, OR_AL_Ib_Test2) {
    OR_CanDo_OR_AI<BYTE>(0x10, 0x01);
}

TEST_F(I8086_ORFixture, OR_AL_Ib_Test3) {
    OR_CanDo_OR_AI<BYTE>(0x00, 0x00);
}

TEST_F(I8086_ORFixture, OR_AL_Ib_Test4) {
    OR_CanDo_OR_AI<BYTE>(0xFF, 0xFF);
}

TEST_F(I8086_ORFixture, OR_AL_Ib_Test5) {
    OR_CanDo_OR_AI<BYTE>(0xFF, 0x00);
}

TEST_F(I8086_ORFixture, OR_AL_Iv_Test1) {
    OR_CanDo_OR_AI<WORD>(0x1111, 0x2222);
}

TEST_F(I8086_ORFixture, OR_AL_Iv_Test2) {
    OR_CanDo_OR_AI<WORD>(0x1010, 0x0101);
}

TEST_F(I8086_ORFixture, OR_AL_Iv_Test3) {
    OR_CanDo_OR_AI<WORD>(0x0000, 0x0000);
}

TEST_F(I8086_ORFixture, OR_AL_Iv_Test4) {
    OR_CanDo_OR_AI<WORD>(0xFFFF, 0xFFFF);
}

TEST_F(I8086_ORFixture, OR_AL_Iv_Test5) {
    OR_CanDo_OR_AI<WORD>(0xFFFF, 0x0000);
}
