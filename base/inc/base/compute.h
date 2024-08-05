#pragma once

#include "base/memory.h"

#include <iostream>
#include <fstream>

class Compute {
    public:
    /**
     * @brief Static function to read a binary file.
     * @param filename Path to the binary file.
     * @param [out] fileSize Number of bytes read.
     * @return Char pointer to data (or nullptr if any error).
     */
    static char* ReadBinary(const char *filename, long long &fileSize) {
        std::ifstream file{filename, std::ios::binary | std::ios::ate};

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
    bool LoadROM(const char *filename, Memory &memory) {
        long long numBytesRead = 0;

        const char* data = ReadBinary(filename, numBytesRead);
        if (!data)
            return false;

        Reset(memory);
        const bool SetSuccess = memory.SetMemory(data, numBytesRead);
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
     */
    virtual void Reset(Memory &memory) noexcept = 0;

public:
    U32 cycles = 0;
};