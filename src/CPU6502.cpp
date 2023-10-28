#include <fstream>
#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory, WORD resetVector) noexcept {
    PC = resetVector;
    SP = 0xFF;

    Status = 0;
    A = X = Y = 0;
    cycles = 0;

    memory.Reset();
}

U32 CPU6502::Run(Memory &memory) {
    bool DecodeSuccess;
    BYTE Instruction;

    do {
        Instruction = FetchByte(memory);
        cycles--;           //leaving only instruction cycles here
        DecodeSuccess = DecodeCommand(Instruction, memory, *this);

        if (DecodeSuccess)
            cycles++;

    } while (DecodeSuccess);

    PC--;                   //revert extra PC increment for last instruction fetching
    return cycles;
}

char* CPU6502::ReadBinary(const char *filename, size_t &fileSize) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        fileSize = 0;
        return nullptr;
    }

    fileSize = file.tellg();

    if (fileSize <= 0) {
        fileSize = 0;
        return nullptr;
    }

    char* result = new char[fileSize];
    file.seekg(0, std::ios::beg);
    file.read(result, fileSize);

    return result;
}

bool CPU6502::LoadROM(const char *filename, Memory& memory, WORD startingAddress) {
    size_t numBytesRead = 0;

    char* data = ReadBinary(filename, numBytesRead);
    if(!data)
        return false;

    Reset(memory, startingAddress);
    for(auto i = 0; i < numBytesRead; i++)
        memory[startingAddress + i] = data[i];
    delete[] data;

    return true;
}
