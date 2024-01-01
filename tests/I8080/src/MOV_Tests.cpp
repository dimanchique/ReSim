#include "I8080_MOV_Tests.h"

void I8080_MOVFixture::RegToRegMov(I8080_OpCodes opcode, BYTE& destRegister, BYTE& srcRegister, BYTE value){
    // given:
    destRegister = ~value;
    srcRegister = value;
    mem[0x0000] = opcode;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(destRegister, value);
    CheckCyclesCount();
}

void I8080_MOVFixture::MemToRegMov(I8080_OpCodes opcode, BYTE& destRegister, WORD srcMemoryAddress, BYTE value){
    // given:
    destRegister = ~value;
    mem[0x0000] = opcode;
    mem[srcMemoryAddress] = value;
    I8080::SwapWordToRegisters(srcMemoryAddress, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(destRegister, value);
    CheckCyclesCount();
}

void I8080_MOVFixture::RegToMemMov(I8080_OpCodes opcode, WORD destMemoryAddress, BYTE value){
    // given:
    mem[destMemoryAddress] = ~value;
    mem[0x0000] = opcode;
    I8080::SwapWordToRegisters(destMemoryAddress, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[destMemoryAddress], value);
    CheckCyclesCount();
}

void I8080_MOVFixture::NopLikeMov(I8080_OpCodes opcode){
    // given:
    uint64_t preSnapshot = *(reinterpret_cast<uint64_t*>(&cpu.A)); //take a snapshot of registers (including status)
    mem[0x0000] = opcode;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);
    uint64_t postSnapshot = *(reinterpret_cast<uint64_t*>(&cpu.A)); //take a snapshot of registers again

    // then:
    EXPECT_EQ(preSnapshot, postSnapshot); // check everything is the same
    CheckCyclesCount();
}
