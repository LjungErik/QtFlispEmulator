#include "memory.h"
#include <cstring>

Memory::Memory():
    m_io(nullptr) {
    std::fill(m_memory.begin(), m_memory.end(), 0);
}

Memory::~Memory() {
    m_io = nullptr;
}

void Memory::copy(MemoryState mem)
{
    for(int i = 0; i < MEMORY_SIZE; i++)
    {
        uint8_t address = i & 0xFF;
        m_memory[address] = mem[address];
    }
}

uint8_t Memory::readMemory(uint8_t address) const
{
    if (m_io != nullptr && m_io->isIOPort(address)) {
        return m_io->readPort(address);
    }

    return m_memory[address];
}

void Memory::writeMemory(uint8_t address, uint8_t data)
{
    if (m_io != nullptr && m_io->isIOPort(address)) {
        m_io->writeOutput(address, data);
    }
    else {
        m_memory[address] = data;
    }
}

MemoryState Memory::exportMemory()
{
    return m_memory;
}
