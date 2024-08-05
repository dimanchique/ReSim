#include "I8080_MOV_Tests.h"

void I8080_MOVFixture::MOV_CanMoveRegToReg(const I8080_OpCodes opcode, BYTE &destRegister, BYTE &srcRegister, const BYTE value){
    // given:
    destRegister = ~value;
    srcRegister = value;
    mem[0x0000] = opcode;
    mem[0x0001] = STOP_OPCODE;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(destRegister, value);
    CheckCyclesCount();
}

void I8080_MOVFixture::MOV_CanMoveMemToReg(const I8080_OpCodes opcode, BYTE &destRegister, const WORD srcMemoryAddress, const BYTE value){
    // given:
    destRegister = ~value;
    mem[0x0000] = opcode;
    mem[0x0001] = STOP_OPCODE;
    mem[srcMemoryAddress] = value;
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(srcMemoryAddress, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(destRegister, value);
    CheckCyclesCount();
}

void I8080_MOVFixture::MOV_CanMoveRegToMem(const I8080_OpCodes opcode, const WORD destMemoryAddress, const BYTE value){
    // given:
    mem[destMemoryAddress] = ~value;
    mem[0x0000] = opcode;
    mem[0x0001] = STOP_OPCODE;
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(destMemoryAddress, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[destMemoryAddress], value);
    CheckCyclesCount();
}

void I8080_MOVFixture::MOV_CanDoNopLikeMove(const I8080_OpCodes opcode){
    // given:
    const uint64_t preSnapshot = *(reinterpret_cast<uint64_t*>(&cpu.A)); //take a snapshot of registers (including status)
    mem[0x0000] = opcode;
    mem[0x0001] = STOP_OPCODE;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);
    const uint64_t postSnapshot = *(reinterpret_cast<uint64_t*>(&cpu.A)); //take a snapshot of registers again

    // then:
    EXPECT_EQ(preSnapshot, postSnapshot); // check everything is the same
    CheckCyclesCount();
}
