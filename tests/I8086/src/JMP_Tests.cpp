#include "I8086_TestingSuite.h"
#include "I8086_OpCodes_Groups.h"

class I8086_JMP_Fixture : public I8086_TestFixture {
protected:
    void TestJump(BYTE opcode, bool condition) {
        // given:
        const DWORD initialPC = cpu.PC;
        cpu.Status.Value = 0; // Clear all flags

        // Set appropriate flags based on opcode
        switch (opcode) {
            case JO_Jb:
                cpu.Status.O = condition;
                break;
            case JNO_Jb:
                cpu.Status.O = !condition;
                break;
            case JB_Jb:
                cpu.Status.C = condition;
                break;
            case JNB_Jb:
                cpu.Status.C = !condition;
                break;
            case JZ_Jb:
                cpu.Status.Z = condition;
                break;
            case JNZ_Jb:
                cpu.Status.Z = !condition;
                break;
            case JBE_Jb:
                cpu.Status.C = cpu.Status.Z = condition;
                break;
            case JA_Jb:
                cpu.Status.C = cpu.Status.Z = !condition;
                break;
            case JS_Jb:
                cpu.Status.S = condition;
                break;
            case JNS_Jb:
                cpu.Status.S = !condition;
                break;
            case JPE_Jb:
                cpu.Status.P = condition;
                break;
            case JPO_Jb:
                cpu.Status.P = !condition;
                break;
            case JL_Jb:
                cpu.Status.S = condition; cpu.Status.O = !condition;
                break;
            case JGE_Jb:
                cpu.Status.S = cpu.Status.O;
                break;
            case JLE_Jb:
                cpu.Status.Z = condition;
                break;
            case JG_Jb:
                cpu.Status.Z = !condition;
                cpu.Status.S = cpu.Status.O;
                break;
            default:
                throw InvalidInstruction();
        }

        mem[effectiveAddress++] = opcode;
        mem[effectiveAddress++] = 0x10; // +16 displacement
        mem[effectiveAddress++] = 0x00;
        mem[effectiveAddress + 0x10] = I8086_STOP_OPCODE;
        mem[effectiveAddress] = I8086_STOP_OPCODE;

        cyclesExpected = condition ? 16 : 4; // Taken: 16, Not taken: 4

        // when:
        cyclesPassed = cpu.Run();

        // then:
        EXPECT_EQ(cpu.PC, initialPC + (condition ? 0x13 : 0x03));
    }
};

// Simple conditional jumps
TEST_F(I8086_JMP_Fixture, JO_Taken)     { TestJump(JO_Jb, true); }
TEST_F(I8086_JMP_Fixture, JO_NotTaken)  { TestJump(JO_Jb, false); }
TEST_F(I8086_JMP_Fixture, JNO_Taken)    { TestJump(JNO_Jb, true); }
TEST_F(I8086_JMP_Fixture, JNO_NotTaken) { TestJump(JNO_Jb, false); }

// Carry flag jumps
TEST_F(I8086_JMP_Fixture, JB_Taken)     { TestJump(JB_Jb, true); }
TEST_F(I8086_JMP_Fixture, JB_NotTaken)  { TestJump(JB_Jb, false); }
TEST_F(I8086_JMP_Fixture, JNB_Taken)    { TestJump(JNB_Jb, true); }
TEST_F(I8086_JMP_Fixture, JNB_NotTaken) { TestJump(JNB_Jb, false); }

// Zero flag jumps
TEST_F(I8086_JMP_Fixture, JZ_Taken)     { TestJump(JZ_Jb, true); }
TEST_F(I8086_JMP_Fixture, JZ_NotTaken)  { TestJump(JZ_Jb, false); }
TEST_F(I8086_JMP_Fixture, JNZ_Taken)    { TestJump(JNZ_Jb, true); }
TEST_F(I8086_JMP_Fixture, JNZ_NotTaken) { TestJump(JNZ_Jb, false); }

// Combined flag jumps
TEST_F(I8086_JMP_Fixture, JBE_Taken_Carry)    { TestJump(JBE_Jb, true); }
TEST_F(I8086_JMP_Fixture, JBE_Taken_Zero)     { TestJump(JBE_Jb, true); }
TEST_F(I8086_JMP_Fixture, JBE_NotTaken)       { TestJump(JBE_Jb, false); }
TEST_F(I8086_JMP_Fixture, JA_Taken)           { TestJump(JA_Jb, true); }
TEST_F(I8086_JMP_Fixture, JA_NotTaken_Carry)  { TestJump(JA_Jb, false); }
TEST_F(I8086_JMP_Fixture, JA_NotTaken_Zero)   { TestJump(JA_Jb, false); }

// Signed jumps
TEST_F(I8086_JMP_Fixture, JL_Taken)      { TestJump(JL_Jb, true); }
TEST_F(I8086_JMP_Fixture, JGE_Taken)     { TestJump(JGE_Jb, true); }
TEST_F(I8086_JMP_Fixture, JLE_Taken_Z)   { TestJump(JLE_Jb, true); }
TEST_F(I8086_JMP_Fixture, JG_Taken)      { TestJump(JG_Jb, true); }

// Negative displacement
TEST_F(I8086_JMP_Fixture, JumpBackwards) {
    // given:
    const DWORD initialPC = cpu.PC;
    cpu.Status.Z = true;
    mem[effectiveAddress - 1] = I8086_STOP_OPCODE;
    mem[effectiveAddress++] = JZ_Jb;
    mem[effectiveAddress++] = 0xFC; // -4 displacement
    mem[effectiveAddress++] = 0xFF;
    mem[effectiveAddress] = I8086_STOP_OPCODE;
    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, initialPC - 1);
}

// Negative displacement
TEST_F(I8086_JMP_Fixture, JumpBackwardsNotTaken) {
    // given:
    const DWORD initialPC = cpu.PC;
    cpu.Status.Z = false;
    mem[effectiveAddress - 1] = I8086_STOP_OPCODE;
    mem[effectiveAddress++] = JZ_Jb;
    mem[effectiveAddress++] = 0xFC; // -4 displacement
    mem[effectiveAddress++] = 0xFF;
    mem[effectiveAddress] = I8086_STOP_OPCODE;
    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, initialPC + 3);
}

// Word displacement
TEST_F(I8086_JMP_Fixture, JumpNearWordDisplacement) {
    // given:
    const DWORD initialPC = cpu.PC;
    cpu.Status.C = true;
    mem[effectiveAddress++] = JB_Jb;
    mem[effectiveAddress++] = 0x00; // Low byte
    mem[effectiveAddress++] = 0x10; // High byte (+0x1000)
    mem[EFFECTIVE_ADDRESS(cpu.PC + 0x1000 + 3, cpu.CS)] = I8086_STOP_OPCODE;
    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, initialPC + 0x1000 + 3);
}

TEST_F(I8086_JMP_Fixture, JMP_Ap) {
    // given:
    cpu.PC = 0x1000;

    mem[0x11000] = JMP_Ap;
    mem[0x11001] = 0x00;
    mem[0x11002] = 0x01; // New PC = 0x0100
    mem[0x11003] = 0x00;
    mem[0x11004] = 0x20; // New CS = 0x2000
    mem[0x20100] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0100);
}

TEST_F(I8086_JMP_Fixture, JMP_Jb) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    mem[0x11000] = JMP_Jb;
    mem[0x11001] = 0x50; // PC offset = +0x0050
    mem[0x11053] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x1053);
}

TEST_F(I8086_JMP_Fixture, JMP_Jv) {
    // given:
    cpu.PC = 0x1000;
    cpu.SP = 0x6000;

    mem[0x11000] = JMP_Jv;
    mem[0x11001] = 0x00;
    mem[0x11002] = 0x01; // PC offset = +0x0100
    mem[0x11103] = I8086_STOP_OPCODE;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x1103);
}

TEST_F(I8086_JMP_Fixture, JMP_GRP5_MP_FarIndirect_Address) {
    cpu.PC = 0x1000;

    ModRegByte modReg;
    modReg.mod = 0b00; // Addr
    modReg.reg = I8086_OpCodes_GRP5::GRP5_JMP_Mp;
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
}
