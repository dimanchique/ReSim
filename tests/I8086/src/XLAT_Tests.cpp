#include "I8086_TestingSuite.h"

class I8086_XLAT_Fixture : public I8086_TestFixture {};

TEST_F(I8086_XLAT_Fixture, XLAT) {
    // given:
    cpu.PC = 0x1000;

    cpu.DS = 0xF000;
    cpu.BX = 0x0040;
    cpu.AL = 0x0F;

    mem[effectiveAddress++] = XLAT;
    mem[effectiveAddress++] = I8086_STOP_OPCODE;

    mem[0xF004F] = 0xDD;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AL, 0xDD);
}
