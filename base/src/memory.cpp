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

void Memory::Reset() {
    memset(mem, 0xFF, size);
}

bool Memory::SetMemory(const char* data, long long int numBytes) {
    if (numBytes == 0 || (numBytes > size))
        return false;
    std::memcpy(mem, data, numBytes);
    return true;
}
