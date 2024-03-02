#pragma once

#include "fstream"
#include "Types.h"
#include "Memory.h"

class CPU_Base{
public:
    /**
     * @brief Static function to read a binary file.
     * @param filename Path to the binary file.
     * @param [out] fileSize Number of bytes read.
     * @return Char pointer to data (or nullptr if any error).
     */
    static char* ReadBinary(const char *filename, long long &fileSize) {
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

        char* const data = new char[fileSize];

        file.seekg(0, std::ios::beg);
        file.read(data, fileSize);

        return data;
    }

    /**
     * @brief Load data into memory from a binary file and a specified starting address.
     * @param filename Path to the binary file.
     * @param memory Memory struct instance.
     * @param startingAddress Starting address to write the binary.
     * @return True if the load was successful; otherwise, false.
     */
    bool LoadROM(const char *filename, Memory &memory, WORD startingAddress) {
        long long numBytesRead = 0;

        const char* data = ReadBinary(filename, numBytesRead);
        if (!data)
            return false;

        Reset(memory, startingAddress);
        const bool SetSuccess = memory.SetMemory(startingAddress, data, numBytesRead);
        delete[] data;

        return SetSuccess;
    }

protected:

    /**
     * @brief CPU execution loop function. Stops execution on invalid instruction.
     * @param memory Memory struct instance.
     * @return Cycles count.
     */
    virtual U32 Run(Memory &memory) = 0;

    /**
     * @brief Resets CPU registers and Stack Pointer to their default values.
     * The Program Counter value after reset depends on the ResetVector value.
     * @param memory Memory struct instance.
     * @param resetVector Program Counter (PC) value after reset. Default value depends on CPU.
     */
    virtual void Reset(Memory &memory, WORD resetVector) noexcept = 0;

public:
    U32 cycles = 0;
};