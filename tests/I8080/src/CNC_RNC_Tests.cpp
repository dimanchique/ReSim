#include "I8080_TestingSuite.h"

class I8080_CNC_RNCFixture : public I8080_TestFixture {
public:
    void CNC_CanCall(const bool canCall, const bool canReturn) {
        // given:
        cpu.Status.C = !canCall;
        mem[0x0000] = CNC;
        mem[0x0001] = 0x3C;
        mem[0x0002] = 0x00;
        // Hack to simulate C flag change in runtime
        mem[0x3C00] = canCall == canReturn ? NOP : CMC;
        mem[0x3C01] = RNC;

        cyclesExpected = 0;
        cyclesExpected += canCall ? 17 : 11;                        // CNC
        cyclesExpected += canCall ? 4 : 0;                          // NOP/CMC
        cyclesExpected += canCall ? (canReturn ? 11 : 5) : 0;       // RNC

        const WORD targetPC = canCall ? (canReturn ? 0x0003 : 0x3C02) : 0x0003;
        mem[targetPC] = STOP_OPCODE;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, targetPC);
        CheckCyclesCount();
    }
};

TEST_F(I8080_CNC_RNCFixture, CNC_CanCallAndCanReturn) {
    CNC_CanCall(true, true);
}

TEST_F(I8080_CNC_RNCFixture, CNC_CanCallAndCannotReturn) {
    CNC_CanCall(true, false);
}

TEST_F(I8080_CNC_RNCFixture, CNC_CannotCall) {
    CNC_CanCall(false, false);
}