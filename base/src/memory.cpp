#include "core/macro.h"

#include "base/memory.h"

#include <cstring>

Memory::Memory(U32 memSize) :
    size(memSize * 1024)
{
    mem = new BYTE[size];
}

Memory::~Memory() {
    delete[] mem;
}

void Memory::Reset(const BYTE resetValue) {
    memset(mem, resetValue, size);
}

bool Memory::SetMemory(U32 address, const char* data, long long int numBytes) {
    if (numBytes == 0 || (address + numBytes >= size))
        return false;
    std::memcpy(mem + address, data, numBytes);
    return true;
}
