#include "I8086_ImpliedOpTests.h"

class I8086_DAA_DAS_Fixture : public I8086_ImpliedOpTests {};

TEST_F(I8086_DAA_DAS_Fixture, DAA_CanAdjust) {
    // mock 0x28 + 0x68 ADD operation
    cpu.AL = 0x90;
    cpu.Status.A = 1;
    TestImpliedInstruction(DAA);
    EXPECT_EQ(cpu.AL, 0x96);
}

TEST_F(I8086_DAA_DAS_Fixture, DAS_CanAdjust) {
    // mock 0x86 - 0x07 SUB operation
    cpu.AL = 0x7F;
    TestImpliedInstruction(DAS);
    EXPECT_EQ(cpu.AL, 0x79);
    EXPECT_EQ(cpu.Status.A, 1);
}
