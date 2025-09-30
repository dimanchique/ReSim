#include "I8086_TestingSuite.h"

class I8086_MOV_Direct_Fixture : public I8086_TestFixture {
  public:
    template<typename T>
    void TestMovImmediateData(const BYTE opCode, WORD targetAddress, T targetValue) {
        // given:
        DWORD targetEffectiveAddress = EFFECTIVE_ADDRESS(targetAddress, cpu.DS);
        mem[targetEffectiveAddress++] = targetValue & 0xFF;
        if (std::is_same_v<T, WORD>)
            mem[targetEffectiveAddress++] = (targetValue >> 8) & 0xFF;

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = targetAddress & 0xFF;
        mem[effectiveAddress++] = (targetAddress >> 8) & 0xFF;
        mem[effectiveAddress] = I8086_STOP_OPCODE;
        // when:
        cyclesPassed = cpu.Run();
    }
};

TEST_F(I8086_MOV_Direct_Fixture, MOV_AL_Ob) {
    cpu.AL = 0x00;
    const BYTE targetValue = 0xDA;
    const WORD targetAddress = 0xAABB;
    TestMovImmediateData(MOV_AL_Ob, targetAddress, targetValue);
    EXPECT_EQ(cpu.AL, targetValue);
}

TEST_F(I8086_MOV_Direct_Fixture, MOV_AX_Ov) {
    cpu.AX = 0x0000;
    const WORD targetAddress = 0xAABB;
    const WORD targetValue = 0xDEAD;
    TestMovImmediateData(MOV_AX_Ov, targetAddress, targetValue);
    EXPECT_EQ(cpu.AX, targetValue);
}

TEST_F(I8086_MOV_Direct_Fixture, MOV_Ob_AL) {
    cpu.AL = 0xDA;
    const WORD targetAddress = 0xAABB;
    const BYTE targetValue = 0x00;
    TestMovImmediateData(MOV_Ob_AL, targetAddress, targetValue);
    EXPECT_EQ(mem[EFFECTIVE_ADDRESS(targetAddress, cpu.DS)], cpu.AL);
}

TEST_F(I8086_MOV_Direct_Fixture, MOV_Ov_AX) {
    cpu.AX = 0xDEAD;
    const WORD targetAddress = 0xAABB;
    const WORD targetValue = 0x0000;
    TestMovImmediateData(MOV_Ov_AX, targetAddress, targetValue);
    EXPECT_EQ(mem[EFFECTIVE_ADDRESS(targetAddress, cpu.DS)], cpu.AX & 0xFF);
    EXPECT_EQ(mem[EFFECTIVE_ADDRESS(targetAddress, cpu.DS) + 1], (cpu.AX >> 8) & 0xFF);
}
